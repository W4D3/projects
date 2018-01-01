/*
 * CASimulator.java
 *
 * Created on September 6, 2007, 3:45 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */



import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Iterator;
import java.util.Locale;
import java.util.Random;
import java.util.Vector;
import javax.imageio.IIOImage;
import javax.imageio.ImageIO;
import javax.imageio.ImageWriteParam;
import javax.imageio.ImageWriter;
import javax.imageio.plugins.jpeg.JPEGImageWriteParam;
import javax.imageio.stream.ImageOutputStream;

/**
 *
 * @author a1flecke
 */
public class CASimulator {
    private int numStates=5;
    private int radius=1;
    private int neighborhood=2*radius+1;
    private int[] seed=new int[200];
    private int experiment;
    private int[] ruleTable=new int[13];
    private int[][] board=new int[1000][seed.length];
    private int numExperiments;
    private double lambdaT;
    private double HT;
    private double lambda;
    private double H;
	private double zeta;
    private Color[] stateColors=new Color[numStates];
    private Vector<Integer> toBeDecimated;
    private Random rand;
    private long randSeed;
    private String ruleString;
    
    
    /** Creates a new instance of CASimulator */
    public CASimulator(int numExperiments) {
        this.numExperiments=numExperiments;
        Random seedRandom = new Random();
        randSeed=seedRandom.nextLong();
        rand=new Random(randSeed);
        
        
        
        //yes this is hard-coded
        stateColors[0]=Color.BLACK;
        stateColors[1]=Color.BLUE;
        stateColors[2]=Color.GREEN;
        stateColors[3]=Color.YELLOW;
        stateColors[4]=Color.ORANGE;
    }
    
    public void simulate(){
	try{
	            File fyle = new File("MasterExperiment.csv");
                FileOutputStream fos = new FileOutputStream(fyle);
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
	            bw.write("Your, Name, \n");
                bw.write("Wrap:,true\n");
                bw.write("K(states):,"+numStates+"\n");
                bw.write("Radius:,"+radius+"\n");
                bw.write("Quiescence:,true\n");
                bw.write("random seed:,"+randSeed+"\n");				
				new File("Experiments").mkdir();
        for(int experiment=0; experiment<numExperiments; experiment++){
			try{
				File f = new File("Experiment_"+experiment+".html");
	            FileOutputStream fs = new FileOutputStream(f);
	            BufferedWriter bwh = new BufferedWriter(new OutputStreamWriter(fs));
				new File("Experiments//experiment_"+experiment).mkdir();
				bwh.write("<html><head><title>Experiment "+experiment+"</title></head>\n");
				bwh.write("<body><center><h1>Experiment "+experiment+"</h1></center><table><tr><th>Step 0</th><th>Step 1</th><th>Step 2</th><th>Step 3</th><th>Step 4</th><th>Step 5</th><th>Step 6</th><th>Step 7</th><th>Step 8</th><th>Step 9</th><th>Step 10</th><th>Step 11</th><th>Step 12</th></tr><tr>\n");
				for(int i=0;i<=12;i++)
					bwh.write("<td><img src=\"Experiments/experiment_"+experiment+"/experiment_"+experiment+"_step"+i+".jpg\" height=\"750px\" width=\"120px\"/></td>\n");
				bwh.write("</tr></table></body></html>\n");
				fs.flush();
                bwh.flush();
                fs.close();
                bwh.close();
			} catch (IOException ie){
			
			
			}
            StringBuilder sb = new StringBuilder();
        
        for(int x=0; x<seed.length; x++){
            seed[x]=rand.nextInt(numStates);
        }
        toBeDecimated=new Vector<Integer>();
        ruleTable[0]=0;
        sb.append(""+0);
        for(int x=1; x<ruleTable.length; x++){
            ruleTable[x]=rand.nextInt(numStates);
            while(ruleTable[x]==0){
                ruleTable[x]=rand.nextInt(numStates);
            }
            toBeDecimated.add(new Integer(x));
            sb.append(""+ruleTable[x]);
        }
        
        //ruleTable=new int[]{0,1,2,3,1,4,1,4,4,1,3,3,3};
        ruleString=sb.toString();
        board[0]=seed;

				bw.write("\n\n");
                bw.write("Experiment #:,"+experiment+"\n");
                bw.write("Rule:,"+ruleString+"\n");
                bw.write("Step,Entry Zeroed,Class,Lambda,Lambda_t,H,H_t,Zeta,Observations\n");
                int indexTo0=0;
                for(int z=0; z<ruleTable.length; z++){
                    calculateLambdaT();
                    calculateLambda();
                    calculateHT();
                    calculateH();
					calculateZeta();
                    if(z==0){
                        bw.write(z+",-,,"+lambda+","+lambdaT+","+H+","+HT+","+zeta+",\n");
                    }else{
                        bw.write(z+","+indexTo0+",,"+lambda+","+lambdaT+","+H+","+HT+","+zeta+",\n");
                    }
                    if(toBeDecimated.size()>0){
                        indexTo0=toBeDecimated.remove(rand.nextInt(toBeDecimated.size()));
                    }
                    for(int x=0; x<board.length-1; x++){
                        for(int y=0; y<board[x].length; y++){
                            board[x+1][y]=ruleTable[calculateMySum(x,y)];
                        }
                    }
                    BufferedImage bi = new BufferedImage(board[0].length,board.length, BufferedImage.TYPE_3BYTE_BGR);
                    Graphics2D g=(Graphics2D)bi.getGraphics();
                    for(int x=0; x<board.length; x++){
                        for(int y=0; y<board[x].length; y++){
                            g.setColor(stateColors[board[x][y]]);
                            g.fillRect(y,x,1,1);
                        }
                    }
                    g.dispose();
                    try{
                        dumpImgToFile( bi, new File("Experiments//experiment_"+experiment+"//experiment_"+experiment+"_step"+z+".jpg") ); 
                    }catch(IOException ie){
                        ie.printStackTrace();
                    }
                    
                    ruleTable[indexTo0]=0;
                    
                }


        }
		        fos.flush();
                bw.flush();
                fos.close();
                bw.close();
	}catch(IOException ie){
                
     }
    }

	// lamda, lamdaT, H, HT
    private void calculateZeta(){
		zeta = 0;
        // Add your zeta calculation here
    }
 
    private void calculateLambdaT(){
        int num0=0;
        for(int x=0; x<ruleTable.length; x++){
            if(ruleTable[x]==0){
                num0++;
            }
        }
        lambdaT=1d-(((double)num0)/((double)ruleTable.length));
        
    }
    
    private void calculateLambda(){
        int num0=0;
        for(int x=0; x<ruleTable.length; x++){
            int newState=ruleTable[x];
            if(newState==0){
                switch(x){
                    case 0:
                        num0+=1;
                        break;
                    case 1:
                        num0+=3;
                        break;
                    case 2:
                        num0+=6;
                        break;
                    case 3:
                        num0+=10;
                        break;
                    case 4:
                        num0+=15;
                        break;
                    case 5:
                        num0+=18;
                        break;
                    case 6:
                        num0+=19;
                        break;
                    case 7:
                        num0+=18;
                        break;
                    case 8:
                        num0+=15;
                        break;
                    case 9:
                        num0+=10;
                        break;
                    case 10:
                        num0+=6;
                        break;
                    case 11:
                        num0+=3;
                        break;
                    case 12:
                        num0+=1;
                        break;
                    default:
                        break;
                }
            }
        }
        lambda=1d-(((double)num0)/(Math.pow((double)numStates, (double)neighborhood)));
    }
    
    private void calculateHT(){
        int[] stateOccurance=new int[numStates];
        for(int x=0; x<ruleTable.length; x++){
            stateOccurance[ruleTable[x]]++;;
        }
        HT=0d;
        double ps;
        for(int x=0; x<numStates; x++){
            ps=((double)stateOccurance[x])/((double)ruleTable.length);
            if(ps!=0){
                double log2ps=Math.log(ps)/Math.log(2);
                HT+=(ps*log2ps);
            }
        }
        
        HT*= -1;
    }
    
    private void calculateH(){
        int[] sumOccurance=new int[ruleTable.length];
        int[] stateOccurance=new int[numStates];
        H=0d;
        for(int x=0; x<ruleTable.length; x++){
            int newState=ruleTable[x];
            switch(x){
                case 0:
                    stateOccurance[newState]+=1;
                    break;
                case 1:
                    stateOccurance[newState]+=3;
                    break;
                case 2:
                    stateOccurance[newState]+=6;
                    break;
                case 3:
                    stateOccurance[newState]+=10;
                    break;
                case 4:
                    stateOccurance[newState]+=15;
                    break;
                case 5:
                    stateOccurance[newState]+=18;
                    break;
                case 6:
                    stateOccurance[newState]+=19;
                    break;
                case 7:
                    stateOccurance[newState]+=18;
                    break;
                case 8:
                    stateOccurance[newState]+=15;
                    break;
                case 9:
                    stateOccurance[newState]+=10;
                    break;
                case 10:
                    stateOccurance[newState]+=6;
                    break;
                case 11:
                    stateOccurance[newState]+=3;
                    break;
                case 12:
                    stateOccurance[newState]+=1;
                    break;
                default:
                    break;
            }
        }
        double ps;
        for(int x=0; x<numStates; x++){
            ps=((double)stateOccurance[x])/(Math.pow((double)numStates, (double)neighborhood));
            if(ps!=0){
                double log2ps=Math.log(ps)/Math.log(2);
                double h=(ps*log2ps);
                H+=h;
            }
        }
        H*= -1;
    }

    private int calculateMySum(int rowIndex, int columnIndex){
        int[] row=board[rowIndex];
        int sum=0;
        //look to my left
        for(int x=radius; x>0; x--){
            int index=columnIndex-radius;
            if(index<0){
                sum+=row[row.length+index];
            }else{
                sum+=row[index];
            }
        }
        //look to my right (and me)
        for(int x=0; x<=radius; x++){
            int index=columnIndex+x;
            if(index>=row.length){
                sum+=row[index-row.length];
            }else{
                sum+=row[index];
            }
        }
        return sum;
        
    }
    
    private int calculateRuleSum(int columnIndex){
        int sum=0;
        //look to my left
        for(int x=radius; x>0; x--){
            int index=columnIndex-radius;
            if(index<0){
                sum+=ruleTable[ruleTable.length+index];
            }else{
                sum+=ruleTable[index];
            }
        }
        //look to my right (and me)
        for(int x=0; x<=radius; x++){
            int index=columnIndex+x;
            if(index>=ruleTable.length){
                sum+=ruleTable[index-ruleTable.length];
            }else{
                sum+=ruleTable[index];
            }
        }
        return sum;
        
    }
    public void dumpImgToFile( BufferedImage img, File f ) throws IOException
    {
        ImageWriter writer = null;
        Iterator iter = ImageIO.getImageWritersByFormatName("jpg");
        if( iter.hasNext() )
            writer = (ImageWriter)iter.next();
        ImageOutputStream ios = ImageIO.createImageOutputStream( f );
            writer.setOutput(ios);

        ImageWriteParam iwparam = new JPEGImageWriteParam( Locale.getDefault() );
        iwparam.setCompressionMode(ImageWriteParam.MODE_EXPLICIT) ;
        iwparam.setCompressionQuality(0.98f);

        writer.write(null, new IIOImage(img, null, null), iwparam);
    } 
    
    public static void main(String[] args) {
        // TODO code application logic here
        if(args.length==0){
            System.out.println("USAGE: java CASimulator NUM_EXPERIMENTS");
            return;
        }
        try{
           CASimulator cas = new CASimulator(Integer.parseInt(args[0]));
        cas.simulate();
        }catch(NumberFormatException nfe){
            System.out.println("USAGE: java CASimulator NUM_EXPERIMENTS");
            return;
        }
        
    }
}


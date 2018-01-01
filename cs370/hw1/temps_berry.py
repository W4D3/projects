#!/usr/bin/env python3
#
#!/usr/bin/env python3
#
# August 2013 High Temps for Knoxville,TN
# August 2013 High Temps for Knoxville,TN
# Hwk 1 for COSC 370 (Summer Sesstion II 2016)
#
from numpy import arange
import matplotlib.pyplot as plt
xData = arange(1,32)    # Ranges for x and y axes must match
tData = [86,87,84,86,86,86,84,83,90,89,88,85,86,79,83,81, \
        75,80,81,85,81,88,89,87,84,85,86,88,88,90,90]
avg = [86.]  # First value for montly avg high temp is just Day 1 temp
tsize=len(tData)
print('Day     High Temp     Monthly Avg')
print('{:3d}{:12.2f}{:15.2f}'.format(1,tData[0],avg[0]))
for i in range(1,tsize) :  # Doubly-nested loop to append average highs
   sum=0                  
   for j in range(0,i+1) :
         sum += tData[j]
   current_avg=sum/float(i+1)
   avg.append(current_avg)    #  Not picky how table is formatted but values
                              #  must match and only 2 decimal places needed.
   print('{:3d}{:12.2f}{:15.2f}'.format(i+1,tData[i],current_avg))

# Plot red points with blue line for original data
plt.plot(xData,tData,'ro',xData,tData,'b-',xData,avg,'g--')
plt.axis([0, 32, 70, 95])  # Show change in average high with green dashed line
plt.grid()
plt.xlabel('Day')
plt.ylabel('High Temp')
plt.title('High Temperatures for Knoxville, TN - August 2013')
plt.text(15,86,'Monthly Avg',color='green')  # Text should be green
plt.show()


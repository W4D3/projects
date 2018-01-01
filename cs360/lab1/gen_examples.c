#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "jrb.h"

char *females[75] = { "Isabella", "Emma", "Olivia", "Ava", "Sophia", "Madison", "Chloe",
"Abigail", "Addison", "Emily", "Ella", "Lily", "Mia", "Grace", "Alexis", "Avery",
"Samantha", "Elizabeth", "Hannah", "Natalie", "Taylor", "Alyssa", "Sarah", "Hailey",
"Riley", "Anna", "Sydney", "Zoe", "Claire", "Leah", "Audrey", "Kaylee", "Sophie",
"Charlotte", "Lillian", "Sofia", "Amelia", "Peyton", "Gabriella", "Lauren", "Julia",
"Maya", "Aubrey", "Bella", "Madelyn", "Brooke", "Brooklyn", "Madeline", "Savannah",
"Morgan", "Layla", "Kayla", "Mackenzie", "Lucy", "Kylie", "Victoria", "Kaitlyn", "Molly",
"Brianna", "Allison", "Evelyn", "Caroline", "Paige", "Eva", "Kate", "Gianna", "Zoey",
"Katelyn", "Alexandra", "Arianna", "Isabelle", "Makayla", "Ellie", "Bailey", "Lilly" };

char *males[75] = { "Jacob", "Noah", "Aiden", "Logan", "Jackson", "Jack", "Ryan",
"Jayden", "Matthew", "Liam", "Joshua", "Tyler", "Benjamin", "Alexander", "Gavin",
"William", "Lucas", "Nathan", "Mason", "Evan", "Michael", "Dylan", "Caleb", "Luke",
"Andrew", "James", "Gabriel", "Elijah", "Connor", "Owen", "Daniel", "Landon", "Nicholas",
"Carter", "Zachary", "Joseph", "Brayden", "Christian", "David", "Max", "Anthony",
"Chase", "Samuel", "Christopher", "John", "Wyatt", "Hunter", "Cameron", "Isaac",
"Cooper", "Austin", "Aidan", "Alex", "Cole", "Henry", "Thomas", "Parker", "Brody", "Ian",
"Isaiah", "Oliver", "Adam", "Jake", "Brandon", "Eli", "Jordan", "Tristan", "Jonathan",
"Julian", "Carson", "Aaron", "Charlie", "Blake", "Xavier", "Dontonio" };

char *lns[400] = {
"Boatman", "Battleground", "Gogh", "Abash", "Jaime", "Tort", "Piracy", "Maelstrom",
"Juicy", "Parsimony", "Benefice", "Konrad", "Hath", "Terrestrial", "Ambulatory",
"Posterior", "Shortfall", "Tempestuous", "Rutland", "Minion", "Recompense", "Felicitous",
"Ideology", "Squatted", "Hamster", "Hitch", "Insert", "Miltonic", "Vial", "Creole",
"Orate", "Reave", "Biology", "Diphthong", "Compile", "Roxbury", "Bridegroom", "Bob",
"Judge", "Ouzo", "Winnie", "Athena", "Ama", "Cancel", "Functionary", "Marathon",
"Hesperus", "Amide", "Demented", "Infinitude", "Joan", "Companionway", "Mysterious",
"Gate", "Invariable", "Deodorant", "Vessel", "Angeline", "Dragnet", "Marina",
"Pollutant", "Headstone", "Tedious", "Cart", "Anastomosis", "Apostolic", "Dichotomize",
"Arrogant", "Turret", "Diem", "Sovereign", "Enable", "Resorcinol", "Blockade",
"Housekeep", "Whiplash", "Print", "Prof", "Amorphous", "Chinamen", "Systemwide",
"Pilferage", "Sneer", "Inexorable", "Fluorescein", "Aerobic", "Beard", "Ilona", "Humane",
"Thiamin", "Electrolytic", "Interstitial", "Topologize", "Fink", "Letitia", "Together",
"Boise", "April", "Shape", "Trinidad", "Spheric", "Lynchburg", "Pharmacology",
"Fossiliferous", "Carmen", "Dysplasia", "Animism", "Frequent", "Huggins", "Patient",
"Hilbert", "Accumulate", "Reginald", "Buzzing", "Playground", "Inflammable", "Mathewson",
"Rightmost", "Inventive", "Fault", "Glen", "Gordian", "Serpent", "Versatile", "Skyway",
"Attendee", "Hillel", "Minerva", "Exhortation", "Cowbell", "Confederate", "Amid", "Muon",
"Sailfish", "Tuscany", "Conjunct", "Lace", "Hurwitz", "Aspartic", "Dodson", "Cayenne",
"Elegiac", "Omitting", "Blunt", "Ride", "Found", "Tadpole", "Flipflop", "Compromise",
"Taught", "Leeuwenhoek", "Savoyard", "Volleyball", "Faustus", "Acumen", "Sic", "Playa",
"Weaken", "Shagging", "Limpkin", "Intuitive", "Douglas", "Constance", "Value", "Lookout",
"Aborigine", "Phonetic", "Tampon", "Cruelty", "Silent", "Madrigal", "Razor",
"Exothermic", "Impediment", "Failsafe", "Muscular", "Prong", "Antagonism", "Dietary",
"Babylonian", "Interest", "Feeble", "Shelve", "Pious", "Whichever", "Wisecrack", "Pius",
"Hierarchal", "Conrad", "Smaller", "Bartlett", "Pinion", "Forrest", "Improvident", "Sow",
"Jorge", "Waldo", "Lasso", "Chummy", "Pen", "Crime", "Cerium", "Astraddle", "Poseur",
"Epicycle", "Shopkeep", "Scanty", "Procyon", "Earthy", "Rectangular", "Fuse",
"Tournament", "Casbah", "Childlike", "Guilford", "Total", "Prod", "Corrosion", "Scold",
"Presentation", "Tollhouse", "Familiar", "Sunflower", "Convivial", "Theseus", "Propel",
"Surfeit", "Finch", "Combustion", "Windshield", "Operon", "Hooves", "Halide", "Citizen",
"Guidebook", "Delude", "Servicemen", "Guiding", "Sluice", "Bronchial", "Ritter",
"Dunkirk", "Reid", "Danielson", "Armload", "Lundquist", "Dervish", "Salesmen", "Sioux",
"Horsefly", "Rove", "Zoom", "Gubernatorial", "Weinstein", "Lilt", "Marksman", "Embroil",
"Handstand", "Diffusible", "Decadent", "Supplant", "Conjoint", "Sovereignty", "Domesday",
"Rant", "Poultice", "Leighton", "Incomplete", "Sanatoria", "Escutcheon", "Overture",
"Decontrolled", "Fairchild", "Argument", "Blackball", "Hereto", "Pandemic", "Univalent",
"Effete", "Innocent", "Courtney", "Wack", "Babe", "Ranier", "Diva", "Turnery", "Awoke",
"Insecure", "Intellect", "Einstein", "Elute", "Patrolled", "Sanitary", "Juxtaposition",
"Plover", "Finicky", "Buttercup", "Fuzz", "College", "Generous", "Hellenic", "Helmsman",
"Third", "Poultry", "Ethos", "Our", "Zeus", "Fog", "Floodlit", "Curl", "Bruise", "Conn",
"Successor", "Cairo", "Expanse", "Courthouse", "Dispel", "Clammy", "Prism", "Bloodstone",
"Transmittance", "Emergent", "Portal", "Disney", "Commensurable", "Explode",
"Terramycin", "Star", "Deject", "Aphelion", "Bloodstain", "Ostrander", "Immiscible",
"Transverse", "Megaton", "Sector", "Cohesive", "Proscribe", "Pipe", "Underclassmen",
"Carbonyl", "Crosshatch", "Bronchiole", "Shoemake", "Flick", "Large", "Gown", "Mayfair",
"Vandal", "Hotbox", "Celeste", "Muskox", "Waist", "Pastel", "Info", "Keen", "Dim",
"Dignify", "Airborne", "Balled", "Morse", "Spain", "Tallahassee", "Figure", "Amend",
"Cavalier", "Dendrite", "Professional", "Rachmaninoff", "Scavenge", "Cheshire", "Ablaze",
"Alveolus", "Noise", "Inexplicit", "Dis", "Alliance", "Roadster", "Compendium", "Shuck",
"Tycoon", "Watchman", "Leafy", "Icebox", "Reminiscent", "Jinx", "Cried", "Pool",
"Desperado", "Ida", "Deane", "Soccer", "Schlesinger", "Nimbus", "Holst", "Salaam",
"Wharves", "Merciful", "Proud", "Valiant" };

char *msuffix[6] = { "Jr", "III", "IV", "Esq", "MD", "PhD" };
char *fsuffix[3] = { "Esq", "MD", "PhD" };

JRB gen_random_name(JRB ptree, int sex)
{
  char name[200];
  char *s;
  int actual_sex;

  while (1) {
    if (sex == 'M' || (sex == 'U' && lrand48()%2 == 0)) {
      strcpy(name, males[lrand48()%75]);
      if (lrand48()%10 == 0) {
        strcat(name, " ");
        strcat(name, males[lrand48()%75]);
      }
      if (lrand48()%99 != 0) {
        strcat(name, " ");
        strcat(name, lns[lrand48()%400]);
      }
      if (lrand48()%12 == 0) {
        strcat(name, " ");
        strcat(name, msuffix[lrand48()%6]);
      }
      actual_sex = 'M';
    } else {
      strcpy(name, females[lrand48()%75]);
      if (lrand48()%10 == 0) {
        strcat(name, " ");
        strcat(name, females[lrand48()%75]);
      }
      if (lrand48()%99 != 0) {
        strcat(name, " ");
        strcat(name, lns[lrand48()%400]);
      }
      if (lrand48()%24 == 0) {
        strcat(name, " ");
        strcat(name, fsuffix[lrand48()%3]);
      }
      actual_sex = 'F';
    }
    if (jrb_find_str(ptree, name) == NULL) {
      s = strdup(name);
      return jrb_insert_str(ptree, s, new_jval_i(actual_sex));
    }
  }
}

main(int argc, char **argv)
{
  int n, type;
  int i;
  JRB ptree, tmp;
  JRB *vec;
  int *permutation, index, itmp;
  int *fathers, *mothers, *a_child;
  Dllist *children, dtmp;
  JRB t;

  srand48(time(0));

  if (argc != 3) {
    fprintf(stderr, "usage: gen_examples n type(int)\n");
    exit(1);
  }

  ptree = make_jrb();

  n = atoi(argv[1]);
  type = atoi(argv[2]);

  vec = (JRB *) malloc(sizeof(JRB) * n);
  for (i = 0; i < n; i++) {
    vec[i] = gen_random_name(ptree, 'U');
  }

  permutation = (int *) malloc(sizeof(int) * n);
  for (i = 0; i < n; i++) permutation[i] = i;
  for (i = n; i > 0; i--) {
    index = lrand48()%i;
    itmp = permutation[i-1];
    permutation[i-1] = permutation[index];
    permutation[index]= itmp;
  }

  children = (Dllist *) malloc(sizeof(Dllist) * n);
  fathers = (int *) malloc(sizeof(int) * n);
  mothers = (int *) malloc(sizeof(int) * n);
  a_child = (int *) malloc(sizeof(int) * n);
  for (i = 0; i < n; i++) { 
    fathers[i] = -1; 
    mothers[i] = -1; 
    a_child[i] = 0;
    children[i] = new_dllist();
  }

  for (i = 1; i < n; i++) {
    if (type == 6) {
      do {
        index = lrand48()%n;
      } while (index == i);
    } else {
      index = lrand48()%i;
    }
    if (vec[index]->val.i == 'M') {
      a_child[i] = 1;
      if (lrand48()%2) {
        fathers[i] = index;
      } else {
        dll_append(children[index], new_jval_i(i));
      }
    }
    if (type == 6) {
      do {
        index = lrand48()%n;
      } while (index == i);
    } else {
      index = lrand48()%i;
    }
    if (vec[index]->val.i == 'F') {
      a_child[i] = 1;
      if (lrand48()%2) {
        mothers[i] = index;
      } else {
        dll_append(children[index], new_jval_i(i));
      }
    }
  }

  if (type == 1) {   /* Generate random unrelated people */
    for (i = 0; i < n; i++) {
      printf("PERSON %s\n", vec[i]->key.s);
      if (lrand48()%4 != 0) {
        printf("  SEX %c\n", vec[i]->val.i);
      }
      printf("\n");
    }
  } else if (type == 2) {   /* Generate line of FATHER_OF/MOTHER_OF */
    for (i = 0; i < n-1; i++) {
      printf("PERSON %s\n", vec[i]->key.s);
      if (lrand48()%2 != 0) {
        printf("  SEX %c\n", vec[i]->val.i);
      }
      printf("  %s %s\n", (vec[i]->val.i == 'M') ? "FATHER_OF" : "MOTHER_OF", vec[i+1]->key.s);
      printf("\n");
    }
  } else if (type == 3) {   /* Generate line of FATHER_OF/MOTHER_OF in random order*/
    for (itmp = 0; itmp < n; itmp++) {
      i = permutation[itmp];
      if (i != n-1) {
        printf("PERSON %s\n", vec[i]->key.s);
        if (lrand48()%2 != 0) {
          printf("  SEX %c\n", vec[i]->val.i);
        }
        printf("  %s %s\n", (vec[i]->val.i == 'M') ? "FATHER_OF" : "MOTHER_OF", vec[i+1]->key.s);
        printf("\n");
      }
    }
  } else if (type == 4) {   /* Generate line of FATHER/MOTHER in random order */
    for (itmp = 0; itmp < n; itmp++) {
      i = permutation[itmp];
      if (i != n-1) {
        printf("PERSON %s\n", vec[i]->key.s);
        if (lrand48()%2 != 0) {
          printf("  SEX %c\n", vec[i]->val.i);
        }
        printf("  %s %s\n", (vec[i+1]->val.i == 'M') ? "FATHER" : "MOTHER", vec[i+1]->key.s);
        printf("\n");
      }
    }
  } else if (type == 5 || type == 6) {   /* use fathers[] and mothers[] */
    for (itmp = 0; itmp < n; itmp++) {
      i = permutation[itmp];
      if (a_child[i] && fathers[i] == -1 && mothers[i] == -1 && lrand48()%2) {
      } else {
        printf("PERSON %s\n", vec[i]->key.s);
        if (lrand48()%2 == 0) {
          if (lrand48()%2 != 0) {
            printf("  SEX %c\n", vec[i]->val.i);
          }
          if (fathers[i] != -1) printf("  %s %s\n", "FATHER", vec[fathers[i]]->key.s);
          if (mothers[i] != -1) printf("  %s %s\n", "MOTHER", vec[mothers[i]]->key.s);
          dll_traverse(dtmp, children[i]) {
            printf("  %s_OF %s\n", (vec[i]->val.i == 'M') ? "FATHER" : "MOTHER", 
                   vec[dtmp->val.i]->key.s);
          }
        } else {
          dll_traverse(dtmp, children[i]) {
            printf("  %s_OF %s\n", (vec[i]->val.i == 'M') ? "FATHER" : "MOTHER", 
                   vec[dtmp->val.i]->key.s);
          }
          if (mothers[i] != -1) printf("  %s %s\n", "MOTHER", vec[mothers[i]]->key.s);
          if (lrand48()%2 != 0) {
            printf("  SEX %c\n", vec[i]->val.i);
          }
          if (fathers[i] != -1) printf("  %s %s\n", "FATHER", vec[fathers[i]]->key.s);
        }
        printf("\n");
      }
    }
  }
}

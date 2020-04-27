
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int segments; //number of pages that memory can hold
int pageNo;
int noofelements=0; //current number of pages in frame
int i=0,j=0;
int noofpages=0; //number of pages
int *pages; //array of pages
char type[50]; //type of placement algorithm
int *frame; //frame array of fifo
int x,y=0;
int pageFaults=0; 
int counter=0;
int flag;
int min,max,compare;
int pointer=0;
int yes;
int compare;


typedef struct{
int page;
int index;
}leastRecentlyUsed;


typedef struct{
int page;
int index;
}optimal;

typedef struct{
int page;
int usedBit;
}clock;


/*void readFile()
{
pages=(int*)malloc(sizeof(int)*2000);
FILE* f;
    f=fopen("inputFIFO2.txt","r");
    if(f != NULL)
    {
            fscanf(f,"%d",&segments);
            fscanf(f,"\n");
            fscanf(f,"%s",type);
            fscanf(f,"\n");
           
        while (!feof(f))
        {
            fscanf(f,"%d",&pageNo); 
            x=pageNo;
            if ( x!=-1)
            {
             pages[noofpages]=x;
             noofpages++;
             fscanf(f,"\n");   
            }            
        }
        fclose(f);
    }
    else printf("File Not Found");
}
*/

void addZero(int x)
{
  if(x<10)
   printf("0%d",x);
   else
   printf("%d",x);
}


void FIFO()
{
   printf("Replacement Policy = FIFO\n");
   printf("-------------------------------------\n");
   printf("Page   Content of Frames\n");
   printf("----   -----------------\n");

  for(int a=0;a<segments;a++)
  frame[a]=-2;

  for(i=0;i<noofpages;i++)
  {
    flag=0;
addZero(pages[i]);
//    printf("%02d",pages[i]);
//check if number is present in frame or not, if yes then we set a flag with 1 and no placement occurs  
  for(j=0;j<segments;j++){
      if(frame[j]==pages[i]){
        flag=1;
       printf("     ");}}
//if number is not present then we have to check for 2 cases, if the frame is not full yet then we add the number and increment the number of elements in the frame, else if the frame is full, then we insert the number using the FIFO procedure( first in- first out) and increment both the counter that moves on the frame and page faults.
    if(flag==0)
   {
    if(noofelements<segments)
    {  frame[noofelements]=pages[i];
       noofelements++;
       printf("     ");
    }
    else if(noofelements==segments)
     {
       frame[counter]=pages[i];
       pageFaults++;
       counter=(counter+1)%segments;
       printf(" F   ");
      }
    }
//printing of the frame
for(y=0;y<segments;y++)
if(frame[y]!=-2){
addZero(frame[y]);
printf(" ");
}printf("\n");
 }printf("-------------------------------------\n");
  printf("Number of page faults = %d\n",pageFaults);
}


void LRU(leastRecentlyUsed* frameLRU)
{ 

   printf("Replacement Policy = LRU\n");
   printf("-------------------------------------\n");
   printf("Page   Content of Frames\n");
   printf("----   -----------------\n");
  
 for(int a=0;a<segments;a++)
  frameLRU[a].page=-2;

  for(i=0;i<noofpages;i++)
   {
     flag=0;
     addZero(pages[i]);
//check if number is present in frame or not, if yes then we set a flag with 1 and no placement occurs and set index with i(current position in pages array)   
 for(j=0;j<segments;j++){
      if(frameLRU[j].page==pages[i])
       {flag=1;
        frameLRU[j].index=i; 
        printf("     ");}}

     if(flag==0)
    { 
//if frame is not full then we insert number to frame smoothly and set its index with i(current position in pages array) and increment the number of elements present, else if frame is full then we loop on the frame to get the position of the element with the minimum and place the new number in that position and update its index and also increment the page faults.

      if(noofelements<segments)
    {  frameLRU[noofelements].page=pages[i];
       frameLRU[noofelements].index=i;
       noofelements++;
       printf("     ");
    }
    
     else if(noofelements==segments)
     {     compare=0; 
           min=1000;
     
      for(int m=0;m<segments;m++)
        if(frameLRU[m].index<min)
       {
          min=frameLRU[m].index;
          compare=m; 
       }
      frameLRU[compare].page=pages[i];
      frameLRU[compare].index=i;
       pageFaults++;
       printf(" F   ");
     }

    }
//printing of the frame
for(y=0;y<segments;y++)
if(frameLRU[y].page!=-2){
addZero(frameLRU[y].page);
printf(" ");}
  printf("\n"); }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d\n",pageFaults);

}


void Optimal(optimal* frameOptimal)
{ 
   printf("Replacement Policy = OPTIMAL\n");
   printf("-------------------------------------\n");
   printf("Page   Content of Frames\n");
   printf("----   -----------------\n");
  for(int a=0;a<segments;a++)
  frameOptimal[a].page=-2;

  for(i=0;i<noofpages;i++)
   {
     flag=0;
     addZero(pages[i]);
//check if number is present in the frame or not, if its found then a flag is set with 1 and the index of this number is updated with the current position in the pages array.
    for(j=0;j<segments;j++){
      if(frameOptimal[j].page==pages[i])
       {flag=1;
        frameOptimal[j].index=i; 
        printf("     ");}}
//if number is not found, if the frame is not full, number is inserted and its index is set with the current position in the page array and number of elements is incremented, else if the frame is full then numbers in the frame will have their indices set with 0 at first and then we loop on the pages array starting from the current position +1 till the end to update indices of numbers in the frame and then replace the old number having the maximum index with the new number
     if(flag==0)
    { 
      if(noofelements<segments)
    {  frameOptimal[noofelements].page=pages[i];
       frameOptimal[noofelements].index=i;
       noofelements++;
       printf("     ");
    }
    
     else if(noofelements==segments)
     {  for(int b=0;b<segments;b++)
         frameOptimal[b].index=0;
    
      for(int m=0;m<segments;m++)
       { for(int n=(i+1);n<noofpages;n++)
          if(pages[n]==frameOptimal[m].page){
            frameOptimal[m].index=n;
            break; }
       }
       compare=0;
      for(int m=0;m<segments;m++){
         if(frameOptimal[m].index==0)
          { compare=m;
            break;}
       else if(frameOptimal[m].index>frameOptimal[compare].index)
          compare=m; 
                                }
      frameOptimal[compare].page=pages[i];
      printf(" F   ");

       pageFaults++;
     }

    }
//printing of the frame
for(y=0;y<segments;y++)
if(frameOptimal[y].page!=-2){
addZero(frameOptimal[y].page);
printf(" ");}
  printf("\n"); }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d\n",pageFaults);
}

void Clock(clock* frameClock)
{ 
   printf("Replacement Policy = CLOCK\n");
   printf("-------------------------------------\n");
   printf("Page   Content of Frames\n");
   printf("----   -----------------\n");

  for(int a=0;a<segments;a++)
  frameClock[a].page=-2;

  for(i=0;i<noofpages;i++)
   {  yes=0;
     flag=0;
     addZero(pages[i]);
//if number is present in the frame, then a flag is set with 1 and its usedBit is also set with 1 
    for(j=0;j<segments;j++){
      if(frameClock[j].page==pages[i])
       {flag=1;
        frameClock[j].usedBit=1;
        printf("     ");
        }}
//if number is not in the frame, if frame is not full then number is inserted and its usedBit is set with 1 and number of elements is incremented. Else if the frame is full, we loop on the frame and if any usedBit is found with zero then the new number is inserted and the usedBit is set with 1 and pointer is incremented, if there are no usedBit with zero, then all of them will be set to zero and then insert the new number and set its usedBit with 1 again.
     if(flag==0)
    { 
      if(noofelements<segments)
    {  frameClock[pointer].page=pages[i];
       frameClock[pointer].usedBit=1;
       noofelements++;
     pointer=(pointer+1)%segments;
     printf("     ");
    }
    else if(noofelements==segments)
    {  
     for(int k=0;k<segments;k++)
    { 
     if(frameClock[pointer].usedBit==0)
     {
       frameClock[pointer].page=pages[i];
       frameClock[pointer].usedBit=1;
       pointer=(pointer+1)%segments;
       yes=1;
     pageFaults++;
       printf(" F   ");
       break;
     }
      else{
       frameClock[pointer].usedBit=0;
       pointer=(pointer+1)%segments;}
    }

   if(yes==0)
   {
     frameClock[pointer].page=pages[i];
     frameClock[pointer].usedBit=1; 
     pointer=(pointer+1)%segments;
     pageFaults++;
      printf(" F   ");
   }

      }

     
}
//printing of the frame
for(y=0;y<segments;y++)
if(frameClock[y].page!=-2){
addZero(frameClock[y].page);
printf(" ");}
  printf("\n"); }
  printf("-------------------------------------\n");
  printf("Number of page faults = %d\n",pageFaults);

}


int main()
{

pages=(int*)malloc(sizeof(int)*2000);
//scans frim the user
            scanf("%d",&segments);
            scanf("\n");
            scanf("%s",type);
            scanf("\n");
           while(1)
            {scanf("%d",&pageNo) ;
             if(pageNo==-1) 
               break;
             pages[noofpages]=pageNo;
             noofpages++;
             scanf("\n");   
            }            

frame=(int*)malloc(sizeof(int)*segments);

leastRecentlyUsed *frameLRU;
frameLRU=malloc(segments*sizeof(leastRecentlyUsed));

optimal *frameOptimal;
frameOptimal=malloc(segments*sizeof(optimal));

clock *frameClock;
frameClock=malloc(segments*sizeof(clock));

if(strcasecmp(type,"FIFO")==0)
FIFO();
if(strcasecmp(type,"LRU")==0)
LRU(frameLRU);
if(strcasecmp(type,"Optimal")==0)
Optimal(frameOptimal);
if(strcasecmp(type,"Clock")==0)
Clock(frameClock);

return 0;
}


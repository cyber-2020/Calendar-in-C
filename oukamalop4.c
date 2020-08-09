/*
            Electrical and Computer Engineering
            **************************************************************************************************************
            Purpose - Print a calendar covering a specified number of months                       
            **************************************************************************************************************
            Data Files
            cp40950.txt - input data file containing physical parameters
            oukamalop4.out - output file to which results will be written 
            **************************************************************************************************************
            
/*Preprocessor Directives*/
    #include <stdio.h>
    #include <math.h>
    #include <string.h>
    
/* function prototypes for void printbigmatrix(), double dumdet(),void myminor() */
int startday(char *month,int year,char *months[ ], int lenmonth[12]);
int leap(int year);

/* main function starts here */
main()
{
/* ************************************************************************************************************* */
    /* variable declarations */
    
    FILE *fin, *fout;   /* pointers to input and output files */
    int yearread;       /*given year*/
    int i,j,k;          /*array indexes*/
    int s;              /*used to output white space*/
    int a;              /*holds the value returned from function startday*/
    int output;         /*counts the # of values outputted, used for determining 'new line'*/
    char monthread[10]; /*holds the month read in*/
    int num;           /*holds the # of months*/
    char *month=&monthread[0];
    
    /*array for holding the names of the months*/
    char *months[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    
    /*holds the # of days in consecutive months*/               
    int lenmonth[]={31,
                    28,
                    31,
                    30,
                    31,
                    30,
                    31,
                    31,
                    30,
                    31,
                    30,
                    31};
    
    
/* ************************************************************************************************************* */
/*                          Begin by opening files & writing title                                               */
/* ************************************************************************************************************* */

        fin = fopen("cp40950.txt","r");
        fout = fopen("oukamalop4.out","w");
        fprintf(fout,"**************************************************************************************\n");
        fprintf(fout,"Electrical and Computer Engineering\n");
        fprintf(fout,"**************************************************************************************\n\n\n");

        
        
/* ************************************************************************************************************* */
/*         Begin input loop, read input parameters, process, output, then loop back until                        */
/*                              end of data file is reached                                                      */
/* ************************************************************************************************************* */
    
    while(fscanf(fin,"%s %d %d",month,&yearread,&num)>0)    /* begin while loop */
    {
        fprintf(fout,"\n\n   New Calendar For %d Months\n",num);
        fprintf(fout,"\t\tBeginning with %s, %d\n",month,yearread);
                
        for(i=0;i<num;i++)    /*outer for loop, used to output consecutive months*/
        {
            output=0;    
            s=0;
            k=0;
            
            /*compares month read in to the names of the months in a year*/
            while(strcmp(month,months[k])!=0)
            {
                k++;    /*holds the number of the month read in the month name array*/
            }
           
            
            /*call function startday*/
            a=startday(months[((k+i)%12)],yearread,months,lenmonth);
            
            /*output calendar's month name and year*/
            fprintf(fout,"%-8s%48d\n",months[((k+i)%12)],yearread);
            
            /*output the names of the week days*/
            fprintf(fout,"Sunday Monday Tuesday Wednesday Thursday Friday Saturday\n");  
            
            /*increments year if december is the next month for calendar to be made*/
            if((i+k)==11||(i+k)==23||(i+k)==35||(i+k)==47||(i+k)==59||(i+k)==71)
                yearread++;
            
            /*inner for loop, outputs the days of the calendar month*/
            for(j=1;j<=lenmonth[(k+i)%12];j++)
            {
                /*while loop, output white space until corresponding start day of the calendar month*/
                while(s<a)
                {
                    fprintf(fout,"\t");
                    s++;    /*increments s*/
                    output++;    /*counts the # of outputs*/
                }
                
                /*if, outputs new line if sunday is the next day of the week*/
                if(output==7||output==14||output==21||output==28||output==35)
                {    fprintf(fout,"\n");    }
                
                /*outputs the corresponding day of the months*/
                fprintf(fout,"  %2d   \t",j);
                output++;    /*counts the # of outputs*/
            }
            fprintf(fout,"\n\n");    /*new line once output of days for a month is complete*/
        }

    
        
    }   /*end of while loop*/     
        
    fclose(fin); fclose(fout);   /* housekeeping */

}    /* end of main */                

/*function startday() determines what day of the week the calendar month starts*/
int startday(char *month,int year,char *months[ ], int lenmonth[12])
{
    int yearStart;    /*day of the week that the given year starts on*/
    int sumDays=0;    /*# of the days passed in current year till calendar start month*/
    int i=0;          /*array index*/
    
        
    if(leap(year)==1)    /*if current year is a leap year, update the february to 29*/
        lenmonth[1]=29;
    else    /*if not leap year, update the february to 28*/
        lenmonth[1]=28;
    
    /*given formula for determining the day that the current year starts on*/
    yearStart=(((int)(((year-1)*365)+floor((year-1)/4)-floor((year-1)/100)+floor((year-1)/400)+1))%7);
    
    /*while, sums the # of days till calendar month in current year*/
    while(strcmp(month,months[i])!=0)
    {
        sumDays=sumDays+lenmonth[i];
        i++;
    }
        return (yearStart+sumDays)%7;    /*returns the # of the day that the calendar month starts*/
    
}

/*function leap() determines whether calendar year is a leap year*/
int leap(int year)
{
    /*if year is {not divisible by 100 and divisible by 4}, or {by 400}*/
    if(((year%100)!=0&&(year%4)==0)||((year%400)==0))
    {
        return 1;
    }
    else   /*if current calendar year is not leap year*/
    {
        return 0;
    }

}
/* ************************************************************************************************************* */
/*                                      END   OF   CODE                                                          */
/* ************************************************************************************************************* */

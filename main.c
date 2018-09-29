#include <stdio.h>
#include <stdlib.h>
#include<mysql.h>
#include<string.h>
struct ID
{
    char name[30];
    int age;
};
void Timetable()
{
    system("cls");
    MYSQL mysql;
    MYSQL_RES * result;
    MYSQL_ROW row;
    int numRecords,numFields,i,j,time,stn,Fchoice;;
    char b;

    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","root","spaproject","project",0,NULL,0))
    {
        printf("Could not connect to MYSQL server\n");
    }


    printf("\t\t\t\tTRAIN TIMETABLE\n\n");
    /*|Train Code|Train name|Start Stn|Destination Stn|Train Time at Start Stn|Stops(Dont Display)|*/
    printf("   TRAIN CODE    TRAIN NAME        START        TIME(24 Hr Format) DESTINATION\n\t");
    if(mysql_query(&mysql,"SELECT Train_no,Train_Name,Start,Start_Time,Destination from Trains")!=0)
    {
        printf("Error in Query27");
    }
    result=mysql_store_result(&mysql);
    numRecords=mysql_num_rows(result);
    numFields=mysql_num_fields(result);

    for(i=0;i<numRecords;i++)
    {
      row = mysql_fetch_row(result);
      fprintf(stdout,"%s\t",row[0]);
      for (j=0;j<numFields;j++)
      {
          fprintf(stdout,"%10s",row[j+1]);
          (j!=(numFields-1))?printf("\t"):printf("\n\t");
      }
    }
    mysql_free_result(result);

    /*printf("Filter Searches? Y/N :");
    scanf("%c",&b);
    scanf("%c",&b);
    printf("\n");
    if(b=='Y'||b=='y')
    {
    system("cls")
    printf("1.Time\n");
    printf("2.Station\n");
    printf("3.Back\n");
    scanf("%d",&Fchoice);
    if(Fchoice==1)
    {
        printf("Enter Starting time(24 Hr Format) : ");
        scanf("%d",&time);
        printf("\n");
        if(time>2400||time<0)
        {
            printf("INVALID INPUTt:\n Please input time between 0000 and 2400\n ");
        }
        else
        {
        printf("\n");
        Search Train Time at Start Stn and print Trains with Starting time>input time
        if(!mysql_query(&mysql,"SELECT Train_no,Train_Name,Start,Start_Time,Destination from Trains where (Start_Time>%d)"))
    {
        printf("Error in Query16");
    }
        }
    }
    else if(Fchoice==2)
    {
        printf("1.Stn1\t2.Stn2\t...\t5.Stn5\n");
        printf("Enter Station : ");
        scanf("%d",&stn);
        Search and print Trains which halt at user's stn

    }
    else if(Fchoice==3)
    {
        main();
    }
    }
    else if(b=='N'||b=='n')
    {
    main();
    }
    else
    {
        printf("Invalid Input\n");
    */
    printf("1.Back\t2.Exit\n");
    scanf("%d",&i);
    if(i==1)
    {
        main();
    }
    else if(i==2)
    {
        exit(1);
    }
    else
    {
        printf("Invalid input");
        Timetable();
    }


}


void main()
{
MYSQL mysql;
MYSQL_RES * result;
MYSQL_ROW row;
MYSQL_FIELD field;
mysql_init(&mysql);
if(!mysql_real_connect(&mysql,"localhost","root","spaproject","Project",0,NULL,0))
{
    printf("Could not connect to MYSQL server\n");
}

system("cls");
int i,j,Mchoice,Fchoice,tcode,time,stn,nseats,sstn,dstn,dist,tcost,ftick=0,htick=0,numRecords,numFields,t1,t2,age,cc;
char a,sstnNm[25],DstnNm[25],name[30],temp1[25],temp2[25],w,c[100];
long int cardno,PNR=0;
struct ID people[30];

   printf("\n============WELCOME TO INDIAN RAILWAYS============\n\n\n");
   printf("Select your choice : \n\n\n");
   printf("1.Train Timetable\n");
   printf("2.Book Tickets\n");
   printf("3.Cancel your Ticket\n");
   printf("4.Check Ticket Status\n");
   printf("5.News Updates\n");
   printf("6.Exit\n");
   printf("======================================================\n");
   printf("enter your choice\n");
    scanf("%d",&Mchoice);

if(Mchoice==1)
{
  Timetable();
}
else if(Mchoice==2)
{
    system("cls");
    printf("1.Check Availaibe Trains\n");
    printf("2.Choose Train\n");
    printf("3.Back\n");
    scanf("%d",&Fchoice);
    if(Fchoice==1)
    {
        Timetable();
    }
    else if(Fchoice==2)
    {
    system("cls");
    printf("Enter Train code : ");
    scanf("%d",&tcode);
    char query[300];
    char query_template[]="SELECT Train_no,Train_name FROM Trains WHERE Train_no='%d'";
    sprintf(query,query_template,tcode);
    if(mysql_query(&mysql,query)!=0)
    {
        printf("Wrong Train code :");
    }
    else{
    if(!(result=mysql_store_result(&mysql)))
    {
        printf("Invalid Train Number");
    }
    else
    {
       row=mysql_fetch_row(result);
       fprintf(stdout,"%s. %s\n",row[0],row[1]);
       mysql_free_result(result);
    }
    /*|Train Code|Train name|*/
    char stops[300];
    char stops_template[]="SELECT Start,H1,H2,H3,H4,H5,H6,H7,H8,H9,H10,H11,Destination FROM Trains WHERE Train_no=%d";
    sprintf(stops,stops_template,tcode);
    mysql_query(&mysql,stops);
    if(!(result=mysql_store_result(&mysql)))
    {
        printf("Empty Result set");
    }
    else
    {
    printf("\n");
    numRecords=mysql_num_fields(result);
    row=mysql_fetch_row(result);
    i=0;
    while(i<numRecords||row[i]=='\0')
    {
        fprintf(stdout,"%d.%s\n",i+1,row[i]);
        i++;
    }
    mysql_free_result(result);
    }
    printf("\nSelect Starting Station and Destination Station :\n");
    scanf("%d%d",&sstn,&dstn);
    char start[100];
    switch(sstn)
    {
        case 1:sprintf(start,"SELECT Start,Start_Time from trains where Train_no=%d",tcode);
            break;
        case 2:sprintf(start,"SELECT H1,H1_Time from trains where Train_no=%d",tcode);
            break;
        case 3:sprintf(start,"SELECT H2,H2_Time from trains where Train_no=%d",tcode);
            break;
        case 4:sprintf(start,"SELECT H3,H3_Time from trains where Train_no=%d",tcode);
            break;
        case 5:sprintf(start,"SELECT H4,H4_Time from trains where Train_no=%d",tcode);
            break;
        case 6:sprintf(start,"SELECT H5,H5_Time from trains where Train_no=%d",tcode);
            break;
        case 7:sprintf(start,"SELECT H6,H6_Time from trains where Train_no=%d",tcode);
            break;
        case 8:sprintf(start,"SELECT H7,H7_Time from trains where Train_no=%d",tcode);
            break;
        case 9:sprintf(start,"SELECT H8,H8_Time from trains where Train_no=%d",tcode);
            break;
        case 10:sprintf(start,"SELECT H9,H9_Time from trains where Train_no=%d",tcode);
            break;
        case 11:sprintf(start,"SELECT H10,H10_Time from trains where Train_no=%d",tcode);
            break;
        case 12:sprintf(start,"SELECT H11,H11_Time from trains where Train_no=%d",tcode);
            break;
        case 13:sprintf(start,"SELECT Destination,DST_Time from trains where Train_no=%d",tcode);
            break;
        default:printf("Invalid Selection");
        break;
      }

  if(mysql_query(&mysql,start)!=0)
    {
        printf("Invalid Station Selected");
    }
    else
    {
    result=mysql_store_result(&mysql);
    row=mysql_fetch_row(result);
    printf("%s-%s\n",row[0],row[1]);
    strcpy(temp1,row[0]);
    t1=atoi(row[1]);
    }
    char dest[100];
    switch(dstn)
    {
        case 1:sprintf(dest,"SELECT Start,Start_Time from trains where Train_no=%d",tcode);
            break;
        case 2:sprintf(dest,"SELECT H1,H1_Time from trains where Train_no=%d",tcode);
            break;
        case 3:sprintf(dest,"SELECT H2,H2_Time from trains where Train_no=%d",tcode);
            break;
        case 4:sprintf(dest,"SELECT H3,H3_Time from trains where Train_no=%d",tcode);
            break;
        case 5:sprintf(dest,"SELECT H4,H4_Time from trains where Train_no=%d",tcode);
            break;
        case 6:sprintf(dest,"SELECT H5,H5_Time from trains where Train_no=%d",tcode);
            break;
        case 7:sprintf(dest,"SELECT H6,H6_Time from trains where Train_no=%d",tcode);
            break;
        case 8:sprintf(dest,"SELECT H7,H7_Time from trains where Train_no=%d",tcode);
            break;
        case 9:sprintf(dest,"SELECT H8,H8_Time from trains where Train_no=%d",tcode);
            break;
        case 10:sprintf(dest,"SELECT H9,H9_Time from trains where Train_no=%d",tcode);
            break;
        case 11:sprintf(dest,"SELECT H10,H10_Time from trains where Train_no=%d",tcode);
            break;
        case 12:sprintf(dest,"SELECT H11,H11_Time from trains where Train_no=%d",tcode);
            break;
        case 13:sprintf(dest,"SELECT Destination,DST_Time from trains where Train_no=%d",tcode);
            break;
        default:printf("Invalid Selection");
        break;
      }

  if(mysql_query(&mysql,dest)!=0)
    {
        printf("Invalid Station Selected");
    }
    else
    {
    result=mysql_store_result(&mysql);
    row=mysql_fetch_row(result);
    printf("%s-%s",row[0],row[1]);
    strcpy(temp2,row[0]);
    t2=atoi(row[1]);
    }
    dist=dstn-sstn;
    if(dist<0)
    {
        printf("\nWrong Route Selected\n Enter any key to continue");
        scanf("%c",&w);
        scanf("%c",&w);
        main();
    }
    system("cls");
    printf("Enter number of Seats : ");
    scanf("%d",&nseats);
    printf("Enter Credit card number : ");
    scanf("%ld",&cardno);
    for(i=0;i<nseats;i++)
    {
        printf("Enter name of Passenger %d :",i+1);
        scanf("%s",people[i].name);

        printf("Enter age of Passenger %d :",i+1);
        scanf("%d",&people[i].age);
        printf("%d",people[i].age);
        if(people[i].age<12)
        {
            htick++;
        }
        else
            {ftick++;}

        long int rcardno=cardno;
        while(cardno!=0)
        {
            PNR=PNR*10+cardno%10;
            cardno=cardno/10;
        }

        sprintf(query,"INSERT INTO T%d (PNR_no,Name,Age,Cardno,temp1,temp2,Time) values(%ld,'%s',%d,%ld,'%s','%s',%d)",tcode,PNR,people[i].name,people[i].age,rcardno,temp1,temp2,t1);
    }
       if(mysql_query(&mysql,query)!=0)
        {
            printf("Invalid values");
        }

    system("cls");
    printf("\nTotal cost : %d\n",(10*dist*ftick)+(5*dist*htick));

    printf("your seat is confirmed \n");
        char check[300];
    char check_template[]="SELECT PNR_no,seat_no,name,age,temp1,temp2,time FROM T%d WHERE PNR_no=%ld";
    sprintf(check,check_template,tcode,PNR);
    mysql_query(&mysql,check);
    if(!(result=mysql_store_result(&mysql)))
    {
        printf("Empty Result set");
    }
    else
    {
    printf("\n");
    numRecords=mysql_num_fields(result);
    row=mysql_fetch_row(result);
    i=0;
  while(i<numRecords||row[i]=='\0')
    {
        switch(i)
        {
        case 0:
        {fprintf(stdout,"\tPNR:%s\n",row[i]);
        i++;}
        break;
        case 1:
        {fprintf(stdout,"\tSeat no:%s\n",row[i]);
        i++;}
        break;
        case 2:
        {fprintf(stdout,"\tName:%s\n",row[i]);
        i++;}
        break;
        case 3:
        {fprintf(stdout,"\tage:%s\n",row[i]);
        i=i+2;}
        break;
        case 4:
        {fprintf(stdout,"\tsource:%s\n",row[i]);
        i++;}
        break;
        case 5:
        fprintf(stdout,"\tdestination:%s\n",row[i]);
        i=i+2;
        break;
        }
    }
    }

  printf("preserve your PNR number for further booking details\n");
    printf("Enter any key to continue");
    scanf("%c",&w);
    scanf("%c",&w);
    main();
    }
    }
}

else if(Mchoice==3)
{
     system("cls");

   printf("Enter Train Number:");
   scanf("%d",&tcode);
   char c[100];
   sprintf(c,"SELECT count(*) From T%d",tcode);
   if(mysql_query(&mysql,c)!=0)
   {
       printf("\nNo such  Train\n");
       printf("Enter any key to continue\n");
       scanf("%c",&w);
       scanf("%c",&w);

   }
   else
   {
   result=mysql_store_result(&mysql);
   row=mysql_fetch_row(result);
   t1=atoi(row[0]);
   printf("t1=%d",t1);
   printf("\nEnter your PNR number :");
   scanf("%d",&PNR);
   printf("\nEnter Name :");
   gets(name);
   gets(name);
   printf("\nEnter Age :");
   scanf("%d",&age);
   char del[100];
   sprintf(del,"DELETE FROM T%d WHERE (PNR_no=%ld) AND (Name='%s') AND (Age=%d)",tcode,PNR,name,age);
   cc=0;
   if(mysql_query(&mysql,del)!=0)
   {
       printf("No such Seat");
       cc++;
   }
     sprintf(c,"SELECT count(*) From T%d",tcode);
   if(mysql_query(&mysql,c)!=0)
   {
       printf("No such Train");
       printf("Enter any key to continue");
       scanf("%c",w);
       main();
   }
   result=mysql_store_result(&mysql);
   row=mysql_fetch_row(result);
   t2=atoi(row[0]);
   if(cc==0&&(t2<t1))
      {
          printf("Your ticket has been cancelled");
          printf("Enter any key to continue");
          scanf("%c",&w);
          scanf("%c",&w);
          main();
      }
    else
    {
      printf("\n No such Booking\nEnter any key to continue");
       scanf("%c",&w);
    }
   }
    }
if(Mchoice==4)
{
    system("cls");
    printf("Enter Train number :");
    scanf("%d",&tcode);
    printf("Enter PNR number :");
    scanf("%ld",&PNR);
    char query[100];
    sprintf(query,"SELECT * FROM T%d WHERE PNR_no=%ld",tcode,PNR);
    mysql_query(&mysql,query);
    if(!(result=mysql_store_result(&mysql)))
    {
        printf("No such booking\n");
    }
    else
    {
    printf("\n");
    printf("==========================================\n");
    numRecords=mysql_num_rows(result);
    row=mysql_fetch_row(result);
    for(i=0;i<numRecords;i++)
    {
        printf("\nPNR Number :%s\n",row[0]);
        printf("Seat Number :%s   Name : %s\n",row[1],row[2]);
        printf("Starting Station :%s  ",row[5]);
        printf("Destination Station :%s  ",row[6]);
        printf("Time :%s",row[7]);
    }
    printf("\n========================================+=\n");
    printf("\n\n\nEnter any key to continue");
    scanf("%c",&w);
    scanf("%c",&w);
    main();
    }
}
else if(Mchoice==5)
{
    system("cls");
    printf("\n1.Big boost for Indian Railways: Narendra Modi govt orders  conversion  of all  Metre Gauge tracks into Broad Gauge\n");
    printf("\n2.Railway extends its strike by a day, skips services on Wednesday too.\n");
    printf("\n3.Two Railway Police Force (RPF) constables saved a 30-year-old commuter from the jaws  of death at Parel railway station on Wednesday morning. \n\n\n");
    printf("\nEnter any key to continue\n");
    scanf("%c",&w);
    scanf("%c",&w);
    main();
}
else if(Mchoice==6)
{

    mysql_close(&mysql);
    exit(1);
}
else
{
    printf("Invalid Input");
    main();
}
}

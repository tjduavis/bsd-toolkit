/*****************************************************
*  BTP100a
*  Ontario Personal Income Tax Return
*  With Validation -version 1.00
*
*  Programmer: Timothy Duavis
*          ID: 019-261-049
*
*  Description:
*       Calculates the data for an Ontario taxpayer
*       on their Income Tax Return.
*       Program uses, if/else statements for special
*       conditions and restrictions.
*
*       The Upgrade to this program is a user input
*       validation, that prevents incompatible 
*       entries based on program conditions.
*
*  Due Date:
*       Oct,10 2004 -at 11:59pm
*  Last Modified:
*       Oct, 10 2004 -at 8:00pm
*
******************************************************/

/*******Defined preprocessor*******/
#include<stdio.h>

/*---Federal values---*/
#include"federal_values.h"

/*---Ontario values---*/
#include"ontario_values.h"

int main(void)
{
/*******Variables*******/
/*---User Data---*/
 double Inc_14;                 /*Employment Income/Total Income*/
 double CPP_16;                 /*CPP Contributions*/
 double EI_18;                  /*EPP Premiums*/
 double Inc_Tax_Ddct_22;        /*Income Tax Deducted*/
 double Stk_Opt_41;             /*Stock Options*/
 double Un_Dues44;              /*Union Dues*/
 int Nod;                       /*Number of Dependents*/

/*---Federal---*/
 double F_rate;
 double F_base,F_Tbase;         /*Federal Base and Tax on Base*/
 double F8;
 double Net_Ftax;               /*Net Federal tax*/

/*---Ontario---*/
 double O_rate;
 double O_base, O_Tbase;        /*Ontario Base and Tax on Base*/
 double P8;
 double Stax_a, Stax_b;         /*surtaxes*/
 double O_tax_lsCrdts;          /*Ontario Tax Less Tax Credits*/
 double O_TAft;                 /*Ontario Tax After Surtaxes*/
 double O_NetTax;               /*Net Provincial tax*/

/*---Other---*/
 double Net_Inc, Tax_Inc;       /*Net Income and Taxable Income*/
 double CPP_Ovrp=0, EI_Ovrp=0;
 double Tot_Pay, Tot_Crdt;      /*Total Payable and Total Credits*/
 double diff, Refund=0, Owing=0;
 int truncated, remainder,rounding_test;
 double decimal;

/*---Validation variables---*/
 int valid;                     /*output variable for scanf*/
 int flag=0;                    /*flag to end do-while loop*/
 char endChk;                   /*to detect any trailing characters*/


/*******Welcome*******/
printf("\nWelcome to the BTP100 Income Tax Return Calculator\n");
printf("==================================================\n\n");
printf("Please enter the T4 slip infomation:\n");

/*******User Data Input*******/
/***With Validations***/

/*do-while loops exit only correct input is entered*/

 do
 {
        printf("\tEmployment Income -\t\tbox 14\t:");
        valid=scanf("%lf%c",&Inc_14,&endChk);

        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(Inc_14<0)
                printf("\t** Income must be non-negative.  Try again. **\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 flag=0;                /*reset for next loop*/

 do
 {
        printf("\tCPP Contributions -\t\tbox 16\t:");
        valid=scanf("%lf%c",&CPP_16,&endChk);

        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(CPP_16<0 || CPP_16>Inc_14)
                printf("\t** CPP must be non-negative and less than income.  "
                                                             "Try again. **\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 flag=0;                /*reset for next loop*/

 do
 {
        printf("\tEmployee's EI premiums -\tbox 18\t:");
        valid=scanf("%lf%c",&EI_18,&endChk);

        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(EI_18<0 || EI_18>Inc_14 && EI_18>CPP_16)
        {
                printf("\t** EI must be non-negative, less than income and CPP."                                                                                "  Try again. **\n");
        }
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 flag=0;                /*reset for next loop*/

 do
 {
        printf("\tIncome Tax Deducted -\t\tbox 22\t:");
        valid=scanf("%lf%c",&Inc_Tax_Ddct_22,&endChk);


        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(Inc_Tax_Ddct_22<0 || Inc_Tax_Ddct_22>Inc_14 && Inc_Tax_Ddct_22>EI_18 &&                                                                 Inc_Tax_Ddct_22>CPP_16)
                printf("\t** Tax deducted must be non-negative and less than income,"
                                                        "CPP and EI.  Try again.  **\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 flag=0;                /*reset for next loop*/

 do
 {
        printf("\tStock Options and Shares -\tbox 41\t:");
        valid=scanf("%lf%c",&Stk_Opt_41,&endChk);

        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(Stk_Opt_41<0)
                printf("\t** Options must be non-negative.  Try again. **\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 flag=0;                /*reset for next loop*/

 do
 {
        printf("\tProfessional/Union Dues -\tbox 44\t:");
        valid=scanf("%lf%c",&Un_Dues44,&endChk);

        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(Un_Dues44<0)
                printf("\t** Dues must be non-negative.  Try again. **\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 printf("\n");
 flag=0;                /*reset for next loop*/

 do
 {
        printf("Number of Dependents -\t\t\t------\t:");
        valid=scanf("%d%c",&Nod,&endChk);

        /*trailing character detected*/
        if(endChk!='\n')
        {
                printf("\t** Trailing characters encountered.  Try again. **\n");

                /*clears input buffer*/
                while(getchar()!='\n')
                {
                        ;/*null statement*/
                }
        }
        else if(Nod<0 || Nod>50)
                printf("\t** Dependents must be non-negative and less than 50."
                                                                "Try again.**\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

/*******Conditions*******/
/*---Federal Rates---*/

 if(Inc_14>=0 && Inc_14<=F_LIMIT1)
    {
        F_rate=F_RATE1;
        F_base=F_BASE1;
        F_Tbase=F_TBASE1;
    }

 else if(Inc_14<=F_LIMIT2)
    {
        F_rate=F_RATE2;
        F_base=F_BASE2;
        F_Tbase=F_TBASE2;
    }

 else if(Inc_14<=F_LIMIT3)
    {
        F_rate=F_RATE3;
        F_base=F_BASE3;
        F_Tbase=F_TBASE3;
    }

 else if(Inc_14>F_LIMIT3)
    {
        F_rate=F_RATE4;
        F_base=F_BASE4;
        F_Tbase=F_TBASE4;
    }

/*---Ontario Rates---*/
  if(Inc_14>=0 && Inc_14<=O_LIMIT1)
    {
        O_rate=O_RATE1;
        O_base=O_BASE1;
        O_Tbase=O_TBASE1;
    }

 else if(Inc_14<=O_LIMIT2)
    {
        O_rate=O_RATE2;
        O_base=O_BASE2;
        O_Tbase=O_TBASE2;
    }

 else if(Inc_14>O_LIMIT2)
    {
        O_rate=O_RATE3;
        O_base=O_BASE3;
        O_Tbase=O_TBASE3;
    }

/*---CPP/EI Overpayments---*/
/*setting the CPP/EI restrictions*/
  if(CPP_16>CPP_MAX)
  {
        CPP_Ovrp=CPP_16-CPP_MAX;
        CPP_16=CPP_MAX;
  }

  if(EI_18>EI_MAX)
  {
        EI_Ovrp=EI_18-EI_MAX;
        EI_18=EI_MAX;
  }

/*******Calculations*******/
  Net_Inc=Inc_14-Un_Dues44;
  Tax_Inc=Net_Inc-Stk_Opt_41;

/*---------Federal Tax-----------*/
  F8=((Tax_Inc-F_base)*F_rate)+F_Tbase;
  Net_Ftax=F8-((F_BEXEMP+CPP_16+EI_18)*F_TCRD_RATE);

  /*negative restriction*/
  if(Net_Ftax<=0)
        Net_Ftax=0;

/*---------Ontario Tax--------------*/
  P8=((Tax_Inc-O_base)*O_rate)+O_Tbase;

  O_tax_lsCrdts=(P8-((O_BEXEMP+CPP_16+EI_18)*O_TCRD_RATE)); /*restriction*/
  if(O_tax_lsCrdts<=0)  /*restriction*/
        O_tax_lsCrdts=0;

  Stax_a=(O_tax_lsCrdts-SURTAXA)*SURTAXA_PRCT;
  Stax_b=(O_tax_lsCrdts-SURTAXB)*SURTAXB_PRCT;

  /*negative restriction*/
  if(Stax_a <0)
        Stax_a=0;

  /*negative restriction*/
  if(Stax_b <0)
        Stax_b=0;

  O_TAft=(O_tax_lsCrdts+Stax_a+Stax_b);
  O_NetTax=(((Nod*DEPDT)+B_RDTN)*2)-O_TAft;

  /*negative restriction*/
  if(O_NetTax<0)
        O_NetTax=0;

  O_NetTax=O_TAft-O_NetTax;

  /*negative restriction*/
  if(O_NetTax<0)
        O_NetTax=0;

/*-----refund or Balance Owing-----*/
  Tot_Pay=(Net_Ftax+O_NetTax);
  Tot_Crdt=Inc_Tax_Ddct_22+CPP_Ovrp+EI_Ovrp;

  diff=Tot_Pay-Tot_Crdt;

/*------Rounding Conversions------*/
  truncated=diff;               /*convert diff into whole value*/
  decimal=diff-truncated;       /*get the decimal*/
  remainder=decimal*1000000;    /*turn decimal into a whole value*/
  remainder/=1000;              /*truncate the last three values*/
  rounding_test=remainder%10;   /*value to determine to round or not*/

  /*greater than 5 and less than -5 do not round up*/
  if(rounding_test<6 && rounding_test>0 || rounding_test>(-6) && rounding_test<0)
  {
        remainder/=10;          /*truncate the test value*/
        decimal=remainder;
        decimal/=100;           /*convert into decimal*/
        diff=truncated+decimal;
  }

  /*negative restriction*/
  if(diff<0)
        Refund=(-diff);
  else
        Owing=diff;

/*******Final Statements*******/
 printf("\n");
 printf("Employment Income (box 14 on all T4 slips)\t\t101\t%.2lf\n",Inc_14);
 printf("Total Income\t\t\t\t\t\t150\t%.2lf\n",Inc_14);
 printf("Net Income\t\t\t\t\t\t236\t%.2lf\n",Net_Inc);
 printf("Taxable Income\t\t\t\t\t\t260\t%.2lf\n",Tax_Inc);
 printf("Net Federal Tax\t\t\t\t\t\t420\t%.2lf\n",Net_Ftax);
 printf("Net Provincial Tax\t\t\t\t\t428\t%.2lf\n",O_NetTax);
 printf("Total Payable\t\t\t\t\t\t435\t%.2lf\n",Tot_Pay);

 printf("Total Income Tax Deducted\t\t437\t%.2lf\n",Inc_Tax_Ddct_22);
 printf("CPP Overpayment\t\t\t\t448\t%.2lf\n",CPP_Ovrp);
 printf("Employment Insurance Overpayment\t450\t%.2lf\n",EI_Ovrp);
 printf("Total Credits\t\t\t\t482\t%.2lf\n",Tot_Crdt);
 printf("Total Payable less Credits\t\t\t\t\t%.2lf\n",diff);
 printf("\n");
 printf("Refund\t\t\t\t\t\t\t484\t%.2lf\n",Refund);
 printf("Balance Owing\t\t\t\t\t\t485\t%.2lf\n",Owing);

 return 0;
}
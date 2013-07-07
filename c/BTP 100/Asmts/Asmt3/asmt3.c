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
*       Oct,25 2004 -at 11:59pm
*  Last Modified:
*       Oct, 2004 -at 
*
******************************************************/

/*******Defined preprocessor*******/
#include<stdio.h>

/*---Federal values---*/
#include"federal_values.h"

/*---Ontario values---*/
#include"ontario_values.h"

/*******Function Prototypes*******/
/*---Buffer Clear---*/
void bufferClear(void);

/*---Input Validation---*/
double InputValid(double value);

/*---Fed_Conditions---*/
void Fed_Conditions(double Inc_14, double *rate, double *base, double *Tbase);

/*---Ont_Conditions---*/
void Ont_Conditions(double Inc_14, double *rate, double *base, double *Tbase);

/*---CPP_EI_Restrictions---*/
void CPP_EI_Restrictions(double *cppOvrp, double *cpp, double *eiOvrp, double *ei);

/*---Results---*/
void results(double *Inc_14, double *CPP_16, double *EI_18, double *Inc_Tax_Ddct_22, double *Stk_Opt_41, double *Un_Dues44, int *Nod, double *F_rate, double *F_base, double *F_Tbase, double *O_rate, double *O_base, double *O_Tbase);

/*---SigDigs---*/
double SigDigs(double diff);

/*---diffRestriction---*/
void diffRestriction(double diff, double Owing, double refund);

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
 double CPP_Ovrp=0, EI_Ovrp=0;

/*---Ontario---*/
 double O_rate;
 double O_base, O_Tbase;        /*Ontario Base and Tax on Base*/

/*---Other---*/
 double chkvalue;		/*value to be checked in InputValid function*/

/*******Welcome*******/
printf("\nWelcome to the BTP100 Income Tax Return Calculator\n");
printf("==================================================\n\n");
printf("Please enter the T4 slip infomation:\n");

/*******User Data Input*******/
/***With Validations***/

printf("\tEmployment Income -\t\tbox 14\t:");
chkvalue=Inc_14;
Inc_14=InputValid(chkvalue);

printf("\tCPP Contributions -\t\tbox 16\t:");
chkvalue=CPP_16;
CPP_16=InputValid(chkvalue);

printf("\tEmployee's EI premiums -\tbox 18\t:");
chkvalue=EI_18;
EI_18=InputValid(chkvalue);

printf("\tIncome Tax Deducted -\t\tbox 22\t:");
chkvalue=Inc_Tax_Ddct_22;
Inc_Tax_Ddct_22=InputValid(chkvalue);

printf("\tStock Options and Shares -\tbox 41\t:");
chkvalue=Stk_Opt_41;
Stk_Opt_41=InputValid(chkvalue);

printf("\tProfessional/Union Dues -\tbox 44\t:");
chkvalue=Un_Dues44;
Un_Dues44=InputValid(chkvalue);

printf("\n");

printf("Number of Dependents -\t\t\t------\t:");
chkvalue=Nod;
Nod=InputValid(chkvalue);

/*******Conditions*******/
Fed_Conditions(Inc_14, &F_rate, &F_base, &F_Tbase);

Ont_Conditions(Inc_14, &O_rate, &O_base, &O_Tbase);

CPP_EI_Restrictions(&CPP_Ovrp, &CPP_16, &EI_Ovrp, &EI_18);

/******Final Calculations and Statements******/
results(&Inc_14, &CPP_16, &EI_18, &Inc_Tax_Ddct_22, &Stk_Opt_41, &Un_Dues44, &Nod, &F_rate, &F_base, &F_Tbase, &O_rate, &O_base, &O_Tbase);

 return 0;
}

/******Function Definitions******/
/*
* Input Validation
*/
double InputValid(double value)
{
 int flag=0;                    /*flag to end do-while loop*/
 int valid;                     /*output variable for scanf*/
 char endChk;                   /*to detect any trailing characters*/
 double value_holder;

 value_holder=value;

 /*do-while loops exit only correct input is entered*/
 do
 {
 	valid=scanf("%lf%c",&value_holder,&endChk);
	
	/*trailing character detected*/
	if(endChk!='\n')
	{
                printf("\t** Trailing characters encountered.  Try again. **\n");
		bufferClear();
        }
        else if(value_holder<0)
                printf("\t** Income must be non-negative.  Try again. **\n");
        else if(valid==2)
                flag=1;

 }while(flag!=1);

 return value_holder;
}

/*
* Buffer Clear
*/
void bufferClear(void)
{
/*clears input buffer*/
while(getchar()!='\n')
	;/*null statement*/
}

/*
* Fed_Conditions
*/
void Fed_Conditions(double Inc_14, double *rate, double *base, double *Tbase)
{

/*---Federal Rates---*/

 if(Inc_14>=0 && Inc_14<=F_LIMIT1)
    {
        *rate=F_RATE1;
        *base=F_BASE1;
        *Tbase=F_TBASE1;
    }

 else if(Inc_14<=F_LIMIT2)
    {
        *rate=F_RATE2;
        *base=F_BASE2;
        *Tbase=F_TBASE2;
    }

 else if(Inc_14<=F_LIMIT3)
    {
        *rate=F_RATE3;
        *base=F_BASE3;
        *Tbase=F_TBASE3;
    }

 else if(Inc_14>F_LIMIT3)
    {
        *rate=F_RATE4;
        *base=F_BASE4;
        *Tbase=F_TBASE4;
    }

}

/* 
* Ont_Conditions
*/
void Ont_Conditions(double Inc_14, double *rate, double *base, double *Tbase)
{
/*---Ontario Rates---*/
  if(Inc_14>=0 && Inc_14<=O_LIMIT1)
    {
        *rate=O_RATE1;
        *base=O_BASE1;
        *Tbase=O_TBASE1;
    }

 else if(Inc_14<=O_LIMIT2)
    {
        *rate=O_RATE2;
        *base=O_BASE2;
        *base=O_TBASE2;
    }

 else if(Inc_14>O_LIMIT2)
    {
        *rate=O_RATE3;
        *base=O_BASE3;
        *Tbase=O_TBASE3;
    }
}

/*
* CPP_EI_Restrictions
*/
void CPP_EI_Restrictions(double *cppOvrp, double *cpp, double *eiOvrp, double *ei)
{
/*---CPP/EI Overpayments---*/
/*setting the CPP/EI restrictions*/
  if(*cpp>CPP_MAX)
  {
        *cppOvrp=*cpp-CPP_MAX;
        *cpp=CPP_MAX;
  }

  if(EI_18>EI_MAX)
  {
        *eiOvrp=*ei-EI_MAX;
        *ei=EI_MAX;
  }

}

/*
* CPP_EI_Restrictions
*/
void results(double *Inc_14, double *CPP_16, double *EI_18, double *Inc_Tax_Ddct_22, double *Stk_Opt_41, double *Un_Dues44, int *Nod, double *F_rate, double *F_base, double *F_Tbase, double *O_rate, double *O_base, double *O_Tbase, double *EI_Ovrp, double *CPP_Ovrp)
{
 double F8;
 double Net_Ftax;               /*Net Federal tax*/
 double P8;
 double Stax_a, Stax_b;         /*surtaxes*/
 double O_tax_lsCrdts;          /*Ontario Tax Less Tax Credits*/
 double O_TAft;                 /*Ontario Tax After Surtaxes*/
 double O_NetTax;               /*Net Provincial tax*/
 double Net_Inc, Tax_Inc;       /*Net Income and Taxable Income*/
 double Tot_Pay, Tot_Crdt;      /*Total Payable and Total Credits*/
 double diff, Refund=0, Owing=0;

/*******Calculations*******/
  Net_Inc=*Inc_14-*Un_Dues44;
  Tax_Inc=Net_Inc-*Stk_Opt_41;

/*---------Federal Tax-----------*/
  F8=((Tax_Inc-*F_base)*(*F_rate))+*F_Tbase;
  Net_Ftax=F8-((F_BEXEMP+CPP_16+EI_18)*(F_TCRD_RATE));

  /*negative restriction*/
  if(Net_Ftax<=0)
        Net_Ftax=0;

/*---------Ontario Tax--------------*/
  P8=((Tax_Inc-*O_base)*(*O_rate))+*O_Tbase;

  O_tax_lsCrdts=(P8-((O_BEXEMP+*CPP_16+*EI_18)*(O_TCRD_RATE))); /*restriction*/
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
  O_NetTax=(((*Nod*(DEPDT))+B_RDTN)*2)-O_TAft;

  /*negative restriction*/
  if(O_NetTax<0)
        O_NetTax=0;

  O_NetTax=O_TAft-O_NetTax;

  /*negative restriction*/
  if(O_NetTax<0)
        O_NetTax=0;

/*-----refund or Balance Owing-----*/
  Tot_Pay=(Net_Ftax+O_NetTax);
  Tot_Crdt=Inc_Tax_Ddct_22+*CPP_Ovrp+*EI_Ovrp;

  diff=Tot_Pay-Tot_Crdt;
  
  diff=sigDigs(diff);

  diffRestriction(&diff, &Owing, &Refund);

 /*******Final Statements*******/
 printf("\n");
 printf("Employment Income (box 14 on all T4 slips)\t\t101\t%.2lf\n",*Inc_14);
 printf("Total Income\t\t\t\t\t\t150\t%.2lf\n",*Inc_14);
 printf("Net Income\t\t\t\t\t\t236\t%.2lf\n",Net_Inc);
 printf("Taxable Income\t\t\t\t\t\t260\t%.2lf\n",Tax_Inc);
 printf("Net Federal Tax\t\t\t\t\t\t420\t%.2lf\n",Net_Ftax);
 printf("Net Provincial Tax\t\t\t\t\t428\t%.2lf\n",O_NetTax);
 printf("Total Payable\t\t\t\t\t\t435\t%.2lf\n",Tot_Pay);

 printf("Total Income Tax Deducted\t\t437\t%.2lf\n",*Inc_Tax_Ddct_22);
 printf("CPP Overpayment\t\t\t\t448\t%.2lf\n",*CPP_Ovrp);
 printf("Employment Insurance Overpayment\t450\t%.2lf\n",*EI_Ovrp);
 printf("Total Credits\t\t\t\t482\t%.2lf\n",Tot_Crdt);
 printf("Total Payable less Credits\t\t\t\t\t%.2lf\n",diff);
 printf("\n");
 printf("Refund\t\t\t\t\t\t\t484\t%.2lf\n",Refund);
 printf("Balance Owing\t\t\t\t\t\t485\t%.2lf\n",Owing);

}

/*
* SigDigs
*/
double SigDigs(double diff)
{
 int truncated, remainder,rounding_test;
 double decimal;

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

 return diff;
}


/*
* diffRestriction
*/
void diffRestriction(double *diff, double *Owing, double *Refund)
{
  /*negative restriction*/
  if(*diff<0)
        *Refund=(-(*diff));
  else
        *Owing=*diff;
}
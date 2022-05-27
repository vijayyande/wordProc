#include"a:calc1.cpp"
void sign(char);
Calculator
	{
	int d,m;
	detectgraph(&d,&m);
	initgraph(&d,&m,"\\tc") ;
	setfillstyle(1,CYAN);
	bar(0,0,getmaxx(),getmaxy());
 //	setbkcolor(CYAN);
	Border border1(SCREEN,240,30,480,330);
	Output output1(&border1,20,20,220,60,BLUE ,WHITE);

	Border border1(SCREEN,240,30,480,330);
	Output output1(&border1,20,20,220,60,BLUE ,WHITE);
	Button button0(&border1,30,230,65,265,BLACK,"0" );
	Button button1(&border1,30,180,65,215,BLACK,"1" );
	Button button2(&border1,78,180,113,215,BLACK,"2" );
	Button button3(&border1,127,180,162,215,BLACK," 3 " );
	Button button4(&border1,30,130,65,165,BLACK," 4 " );
	Button button5(&border1,78,130,113,165,BLACK," 5 " );
	Button button6(&border1,127,130,162,165,BLACK," 6 " );
	Button button7(&border1,30,80,65,115,BLACK," 7 " );
	Button button8(&border1,78,80,113,115,BLACK,"8" );
	Button button9(&border1,127,80,162,115,BLACK," 9 " );
	Button buttonDiv(&border1,175,80,210,115,BLACK," / " );
	Button buttonMul(&border1,175,130,210,165,BLACK," * " );
	Button buttonSub(&border1,175,180,210,215,BLACK," - " );
	Button buttonDot(&border1,78,230,113,265,BLACK," ." );
	Button buttonClr(&border1,127,230,162,265,BLACK," clr " );
	Button buttonAdd(&border1,175,230,210,265,BLACK," += " );

	button7.Display();  button8.Display();  button9.Display();
	button4.Display();  button5.Display();  button6.Display();
	button1.Display();  button2.Display();  button3.Display();
	buttonSub.Display();buttonDiv.Display();
	buttonMul.Display();buttonAdd.Display();
	button0.Display();buttonDot.Display();buttonClr.Display();
	output1.Number(0.0);

	const char ESC=27;
	char dstring[80];
	char tempbuf[80];
	int numchars = 0;
	char ch;
	char oper;
	boolean isfirst = true;
	boolean chain = false;
	double number1,number2;
	double answer=0;

	while ((ch=getch()) != ESC )
		{
		if( (ch>='0' && ch<='9')|| ch=='.')
		{
		switch(ch)
			{
			case '0': button0.Click();break;
			case '1': button1.Click();break;
			case '2': button2.Click();break;
			case '3': button3.Click();break;
			case '4': button4.Click();break;
			case '5': button5.Click();break;
			case '6': button6.Click();break;
			case '7': button7.Click();break;
			case '8': button8.Click();break;
			case '9': button9.Click();break;
			case '.': buttonDot.Click();break;

			default:
			   sound(5000);delay(450);nosound();break;
			}
			dstring[numchars++] = ch;
			dstring[numchars] = '\0';
			 if( atof( dstring ) > 99999999999.99 || numchars > 11 )
			  {
			  delay(100);sound(1000);delay(300),nosound();
			  dstring[--numchars] = '\0';
			  }
			  output1.Text(dstring);
			  }

			 else if ( ch=='/' || ch=='-' || ch=='+' || ch=='='|| ch == '*')
			 {
			 strcpy(tempbuf,dstring);
			 numchars= 0;
			 dstring[numchars] = '\0';
			 output1.Text(dstring);
			 if (isfirst)
				{
				number1=(chain) ? answer : atof(tempbuf);
				isfirst=false;
				switch(ch)
				  {
				  case '/': buttonDiv.Click();  oper='/';sign('/');
				  break;
				  case '*': buttonMul.Click();  oper='*';sign('*');
				  break;
				  case '-': buttonSub.Click();  oper='-';sign('-');
				  break;
				  case '+': buttonAdd.Click();  oper='+';sign('+');
				  break;
				  case '=': buttonAdd.Click();  oper='=';sign('=');
				  break;
				  default:sound(1000);delay(200);nosound();break;
				   }
				 }
				  else
				  {
				  buttonAdd.Click();
				  number2 = atof(tempbuf);
				  switch(oper)
				  {
				  case '/': answer = number1 / number2;break;
				  case '*': answer = number1 * number2;break;
				  case '-': answer = number1 - number2;break;
				  case '+': answer = number1 + number2;break;
				  }
				  if( answer > 99999999999.99)
				    output1.Text("Overflow");
				   else
					{
					output1.Number(answer);
					number1 = answer;
				    }
				    isfirst  = true;
				    chain = true;
				    }
				   }
				  else if ( ch=='C' || 'c')
				{
				buttonClr.Click();
				isfirst = true;
				chain = false;
				numchars = 0;
				dstring[numchars] = '\0';
				output1.Number(0.0);
				}
				else
				{
				delay(100);sound(1000);delay(300);nosound();
				}
			     }
			       //	return 0;
				//closegraph();
				return 0;
				}


void sign(char a)
{
   char c[1];
   c[1] = 0;
   c[0] = a;

	setfillstyle(1,15);
	bar(270,60,320,80);
	setcolor(0);
	outtextxy(275,65,&c[0]);
return;
}



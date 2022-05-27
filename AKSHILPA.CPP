#include <dos.h>

 wordings()
  {
   sound(880);		delay(270);		nosound();
   sound(740);		delay(270);		nosound();
   sound(580);		delay(270);		nosound();
   sound(540);		delay(270);		nosound();
   sound(490);		delay(270);		nosound();
   sound(540);		delay(1400);		nosound();
   sound(490);		delay(270);		nosound();
   sound(540);		delay(100);		nosound();
   sound(490);		delay(100);		nosound();
   sound(430);		delay(170);		nosound();		delay(500);

   sound(430);		delay(270);		nosound();
   sound(490);		delay(300);		nosound();
   sound(540);		delay(370);		nosound();
   sound(430);		delay(250);		nosound();
   sound(490);		delay(270);		nosound();		delay(500);

   sound(430);		delay(270);	    nosound();
   sound(370);		delay(270);		nosound();
   sound(430);		delay(270);		nosound();
   sound(370);		delay(270);		nosound();
   sound(580);		delay(270);		nosound();
   sound(490);		delay(200);		nosound();

   return 0;
  }

 stmusic()
  {

   sound(880);		delay(100);		nosound();		delay(25);
   sound(970);		delay(100);		nosound();      delay(25);
   sound(970);		delay(100);		nosound();      delay(25);
   sound(880);		delay(100);		nosound();      delay(25);
   sound(970);		delay(100);		nosound();      delay(100);
   sound(880);		delay(100);		nosound();      delay(25);
   sound(970);		delay(100);		nosound();      delay(800);

   sound(880);		delay(100);		nosound();		delay(200);
   sound(970);		delay(100);		nosound();      delay(300);
   sound(970);		delay(100);		nosound();      delay(300);
   return 0;
 }

 mukhada()
  {
   sound(840);		delay(300);		nosound();		delay(50);
   sound(840);		delay(300);		nosound();
   sound(970);		delay(300);		nosound();
   sound(840);		delay(700);		nosound();		delay(100);

   sound(660);		delay(300);	    nosound();
   sound(740);		delay(300);		nosound();      delay(50);
   sound(740);		delay(300);		nosound();
   sound(880);		delay(300);		nosound();
   sound(740);		delay(700);		nosound();		delay(100);

   return 0;
 }
   //****************************************************
 mukhada1()
  {
   sound(540);		delay(300);		nosound();		delay(15);
   sound(540);		delay(300);		nosound();      delay(15);
   sound(540);		delay(300);		nosound();      delay(15);
   sound(540);		delay(300);		nosound();      delay(15);

   sound(580);		delay(300);		nosound();
   sound(660);		delay(300);		nosound();
   sound(740);		delay(250);		nosound();
   sound(540);		delay(250);		nosound();
   sound(740);		delay(250);		nosound();
   sound(540);		delay(250);		nosound();
   sound(740);		delay(250);		nosound();
   sound(540);		delay(250);		nosound();
   sound(740);		delay(250);		nosound();
   sound(540);		delay(250);		nosound();
   sound(740);		delay(200);		nosound();
//   sound(840);		delay(200);		nosound();

//   return 0;
//  }
   //****
   nosound();		delay(300);

   sound(840);		delay(125);		nosound();
   sound(880);		delay(125);		nosound();
   sound(840);		delay(200);		nosound();
   sound(660);		delay(300);		nosound();

   sound(540);		delay(400);		nosound();
   sound(660);		delay(400);		nosound();
   sound(740);		delay(300);		nosound();


   sound(840);		delay(250);		nosound();
   sound(740);		delay(250);		nosound();
   sound(840);		delay(250);		nosound();
   sound(740);		delay(150);		nosound();
   sound(880);		delay(200);		nosound();
   nosound();		delay(50);
   sound(880);		delay(150);		nosound();
   sound(740);		delay(300);		nosound();
   sound(840);		delay(300);		nosound();
   sound(740);		delay(200);		nosound();

   //  Next Part Second Time

   nosound();		delay(300);

   sound(420);		delay(125);		nosound();
   sound(440);		delay(125);		nosound();
   sound(420);		delay(200);		nosound();
   sound(330);		delay(300);		nosound();

   sound(270);		delay(400);		nosound();
   sound(330);		delay(400);		nosound();
   sound(420);		delay(300);		nosound();

   sound(440);		delay(250);		nosound();
   sound(420);		delay(250);		nosound();
   sound(440);		delay(250);		nosound();
   sound(420);		delay(150);		nosound();
   sound(485);		delay(200);		nosound();
   nosound();  		delay(50);
   sound(485);		delay(150);		nosound();
   sound(420);		delay(300);		nosound();
   sound(440);		delay(300);		nosound();
   sound(840); sound(420);		delay(200);		nosound();

   //****
   nosound();		delay(300);

   sound(420);		delay(125);		nosound();
   sound(440);		delay(125);		nosound();
   sound(420);		delay(200);		nosound();
   sound(330);		delay(300);		nosound();

   sound(270);		delay(400);		nosound();
   sound(330);		delay(400);		nosound();
   sound(370);		delay(300);		nosound();


   sound(420);		delay(250);		nosound();
   sound(370);		delay(250);		nosound();
   sound(420);		delay(250);		nosound();
   sound(370);		delay(150);		nosound();
   sound(440);		delay(200);		nosound();
   nosound();		delay(50);
   sound(440);		delay(150);		nosound();
   sound(370);		delay(300);		nosound();
   sound(420);		delay(300);		nosound();
   sound(370);		delay(200);		nosound();


return 0;
}


/*   sound(840);		delay(300);		nosound();
   sound(880);		delay(300);		nosound();
   sound(740);		delay(500);		nosound();*/

 main()
 {

   stmusic();		delay(500);
   stmusic();
   wordings();      delay(500);
   wordings();		delay(500);
   mukhada();		delay(100);
   mukhada();       delay(100);
   mukhada1();      delay(500);
   wordings();

   return 0;

 }
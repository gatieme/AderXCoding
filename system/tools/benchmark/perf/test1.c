 //test.c
 void longa()
 {
   int i,j;
   for(i = 0; i < 1000000; i++)
   j=i; //am I silly or crazy? I feel boring and desperate.
 }

 void foo2()
 {
   int i;
   for(i=0 ; i < 10; i++)
        longa();
 }

 void foo1()
 {
   int i;
   for(i = 0; i< 100; i++)
      longa();
 }

 int main(void)
 {
   foo1();
   foo2();
}

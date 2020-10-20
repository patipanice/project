/**
 * helloworld
 */

public class helloworld {
   public static void main(String[] args) {

      int[] cardB = new int[] {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
      int j = 0;
      int[] A = new int[52];
     // int[13] B = {};
      //int[] C = {};
     //int[] D = {};
      for(int i = 0; i<=9 ; i++){
         A[i] = cardB[j];
         B[i+1]= card[i+1];
        C[i+2]= card[i+1];
         D[i+3]= card[i+1];
         j = j+4;
       }
       System.out.println(A[2]);
   }
    
}
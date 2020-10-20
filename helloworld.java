/**
 * helloworld
 */

public class helloworld {
   public static void main(String[] args) {

      int[] cardB = new int[] {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51};
      int j = 0;
      int[] A = new int[13];
      int[] B = new int[13];
      int[] C = new int[13];
      int[] D = new int[13];
      for(int i = 0; i<=12 ; i++){
         A[i] = cardB[j];
         B[i] = cardB[j+1];
         C[i] = cardB[j+2];
         D[i] = cardB[j+3];
         j = j+4;
       }
       System.out.println(D[12]);
   }
    
}
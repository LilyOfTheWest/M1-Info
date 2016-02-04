/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Lily
 */
public class Compute implements Compute_itf{
    
    @Override
    public int plus(int a, int b) {
        return a+b;
    }

    @Override
    public int minus(int a, int b) {
        return a-b;
    }

    @Override
    public int factorial(int a) {
        for(int i=a-1;i>0;i--){
            a*=i;
        }
        return a;
    }
}

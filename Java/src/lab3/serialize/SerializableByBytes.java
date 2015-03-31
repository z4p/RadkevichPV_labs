/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package lab3.serialize;


/**
 *
 * @author z4p
 */
public interface SerializableByBytes {
    public byte[] serialize();
    public void deserialize(byte[] a);
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Bloque : MonoBehaviour
{
    public GameObject particulas;
    public Puntos puntos;
    public AudioSource punto;
   void OnCollisionEnter()
    {
        Instantiate(particulas, transform.position, Quaternion.identity);
        puntos.GanarPunto();
        punto.Play();
        transform.SetParent(null);
        Destroy(gameObject);
       
        
    }
}

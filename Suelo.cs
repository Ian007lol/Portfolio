using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Suelo : MonoBehaviour
{
    public Vidas vidas;
    public AudioSource error;
    // Start is called before the first frame update
  void OnTriggerEnter()
    {
        vidas.PerderVida();
        error.Play();
    }
}

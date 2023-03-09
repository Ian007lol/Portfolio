using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Iniciar : MonoBehaviour
{
    // Start is called before the first frame update

    public bool iniciar;
    public ElementoInteractivo pulsar;
    // Update is called once per frame
    void Update()
    {
        if ((pulsar.pulsado || Input.GetButtonDown("Fire1")) && iniciar) {
            Puntos.puntos = 0;
            Vidas.vidas = 3;
            SceneManager.LoadScene("Nivel 01");
        }
        
    }
}

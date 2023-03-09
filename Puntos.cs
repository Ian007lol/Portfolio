using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Puntos : MonoBehaviour
{
    
    public static int puntos = 0;
    public Text TextoPuntos;
    public GameObject Victoria;
    public MovimientoBarra barra;
    public MovimientoBola bola;
    public SiguienteNivel siguienteNivel;
    public GameObject nivelCompletado;
    public GameObject juegoCompletado;
    public Transform Destructibles;
    public AudioSource completado;
    public AudioSource musica;
    // Start is called before the first frame update
    void Start()
    {
        ActualizarMarcadorDePuntos();
    }
    public void ActualizarMarcadorDePuntos()
    {
        TextoPuntos.text = "Puntos : " + Puntos.puntos;
    }
    // Update is called once per frame
    public void GanarPunto()
    {


        // if (puntos >= 28) return;
        Puntos.puntos++;
        ActualizarMarcadorDePuntos();
       
        if(Destructibles.childCount <= 1)
        {
            Debug.Log("UWU");
            bola.DetenerMovimiento();
            barra.enabled = false;
            musica.Stop();
            if (siguienteNivel.EsUltimoNivel())
            {
                juegoCompletado.SetActive(true);
                completado.Play();
            }
            else
            {
                nivelCompletado.SetActive(true);
                completado.Play();

            }
            siguienteNivel.ActivarCarga();
        }

        /*  if (puntos >= 28)
          {
              
          }*/
    }
    
}

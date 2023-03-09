using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Vidas : MonoBehaviour
{
    public MovimientoBarra barra;
    public MovimientoBola bola;
    public static int vidas = 3;
    public GameObject Gameover;
    public SiguienteNivel siguienteNivel;
    public Text textoVidas;
    public AudioSource GameOver;
    public AudioSource tuhermana;
    // Start is called before the first frame update
    void Start()
    {
        textoVidas.text = "Vidas : " + vidas;
        
        ActualizarMarcadorVidas();
    }
    public void ActualizarMarcadorVidas()
    {
textoVidas.text = "Vidas : " + Vidas.vidas;
    }
    public void PerderVida()
    { if (vidas <= 0) return;
        Vidas.vidas--;
        ActualizarMarcadorVidas();

        if (Vidas.vidas == 0)
        {
            //Mostraremos Gameover

            Gameover.SetActive(true);
            tuhermana.Stop();
            GameOver.Play();

            bola.DetenerMovimiento();
            barra.enabled = false;
            siguienteNivel.nivelACargar = "Portada";
            siguienteNivel.ActivarCarga();
            
        }
        else
        {
        barra.Reset();

            bola.DetenerMovimiento();
            bola.Reset();
        }

       
        
    }
}

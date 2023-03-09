using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovimientoBola : MonoBehaviour
{
    public float velocidadInicial = 600f;
    public AudioSource impacto;
    public GameObject instruccion;
    public ElementoInteractivo screen;
    //agrego referencia al Rigidbody para que la variable pueda acceder a el.
    public Rigidbody rig;

    public Transform barra;
    bool enJuego = false;

    Vector3 posicionInicial;

  

    // Start is called before the first frame update
    void Start()
    {
        posicionInicial = transform.position;
        
    }
    public void Reset()
    {
        transform.position = posicionInicial;
        transform.SetParent(barra);
        enJuego = false;
    }
    public void DetenerMovimiento()
    {
        rig.isKinematic = true;

        rig.velocity = Vector3.zero;
    }


    // Update is called once per frame
    void Update()
    {
        if (!enJuego && (Input.GetButtonDown("Fire1") || screen.pulsado))
        {
            instruccion.SetActive(false);
            transform.SetParent(null);
            rig.isKinematic = false;
            rig.AddForce(new Vector3(velocidadInicial, velocidadInicial, 0));
            enJuego = true;
        }
        
    }
   
}

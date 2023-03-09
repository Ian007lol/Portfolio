using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovimientoBarra : MonoBehaviour
{

    public float velocidad = 0.1f;
    public ElementoInteractivo pulsarizquierdo;
    public ElementoInteractivo pulsarderecho;
    float pulsado;
    Vector3 posicionInicial;
    // Start is called before the first frame update
    void Start()
    {
        posicionInicial = transform.position;
    }

    public void Reset()
    {
        transform.position = posicionInicial;
    }

    // Update is called once per frame
    void Update()
    {
        if (pulsarizquierdo.pulsado)
        {
            pulsado = -1;
        }
        else if (pulsarderecho.pulsado)
        {
            pulsado = 1;
        }
        else
        {
            pulsado = Input.GetAxisRaw("Horizontal");
        }
       
        float posX = transform.position.x + (pulsado * velocidad * Time.deltaTime);

        transform.position = new Vector3(Mathf.Clamp(posX, -10, 10), transform.position.y, transform.position.z);
    }
   
}

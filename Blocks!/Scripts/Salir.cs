using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Salir : MonoBehaviour
{
    public bool salir;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            if (salir)
            {
                Application.Quit();
                
            }
            else
            {
                SceneManager.LoadScene("Portada");
            }
            
        }
    }
}

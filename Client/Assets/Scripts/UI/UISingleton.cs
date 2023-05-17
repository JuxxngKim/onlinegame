using System;
using UnityEngine;
using UnityEngine.Events;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;


public class UISingleton<typeT> : MonoBehaviour where typeT : UISingleton<typeT>
{
    private static typeT _instance;
    
    public static typeT Instance
    {
        get
        {
            return _instance;
        }
    }

    private void Awake()
    {
        _instance = (typeT)this;
    }

    public virtual void Show()
    {
        this.gameObject.SetActive(true);
    }

    public virtual void Hide()
    {
        this.gameObject.SetActive(false);
    }
}
﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager
{
    int _order = 10;

    Stack<MonoBehaviour> _popupStack = new Stack<MonoBehaviour>();
    public MonoBehaviour SceneUI { get; private set; }

    private GameObject _root;

    public GameObject Root
    {
        get
        {
            if (_root != null)
                return _root;
            
            var root = Resources.Load<GameObject>("Prefabs/UI/UIRoot");
            _root = GameObject.Instantiate(root);
            
            var toastPopup = Resources.Load<GameObject>("Prefabs/UI/ToastPopupFactory");
            GameObject.Instantiate(toastPopup, _root.transform);
            
            GameObject.DontDestroyOnLoad(_root);
            return _root;
        }
    }

    public void SetCanvas(GameObject go, bool sort = true)
    {
        Canvas canvas = Util.GetOrAddComponent<Canvas>(go);
        canvas.renderMode = RenderMode.ScreenSpaceOverlay;
        canvas.overrideSorting = true;

        if (sort)
        {
            canvas.sortingOrder = _order;
            _order++;
        }
        else
        {
            canvas.sortingOrder = 0;
        }
    }
    
	public T ShowSceneUI<T>(string name = null) where T : MonoBehaviour
	{
		if (string.IsNullOrEmpty(name))
			name = typeof(T).Name;

		GameObject go = Managers.Resource.Instantiate($"UI/{name}");
		T sceneUI = Util.GetOrAddComponent<T>(go);
        SceneUI = sceneUI;

		go.transform.SetParent(Root.transform, false);

		return sceneUI;
	}

	public T ShowPopupUI<T>(string name = null) where T : MonoBehaviour
    {
        if (string.IsNullOrEmpty(name))
            name = typeof(T).Name;

        GameObject go = Managers.Resource.Instantiate($"UI/Popup/{name}");
        T popup = Util.GetOrAddComponent<T>(go);
        _popupStack.Push(popup);

        go.transform.SetParent(Root.transform, false);

		return popup;
    }

    public void ClosePopupUI(MonoBehaviour popup)
    {
		if (_popupStack.Count == 0)
			return;

        if (_popupStack.Peek() != popup)
        {
            Debug.Log("Close Popup Failed!");
            return;
        }

        ClosePopupUI();
    }

    public void ClosePopupUI()
    {
        if (_popupStack.Count == 0)
            return;

        MonoBehaviour popup = _popupStack.Pop();
        Managers.Resource.Destroy(popup.gameObject);
        popup = null;
        _order--;
    }

    public void CloseAllPopupUI()
    {
        while (_popupStack.Count > 0)
            ClosePopupUI();
    }

    public void Clear()
    {
        CloseAllPopupUI();

        if (SceneUI != null)
        {
            Managers.Resource.Destroy(SceneUI.gameObject);
            SceneUI = null;
        }
    }
}

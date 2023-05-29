using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoginScene : BaseScene
{
    protected override void Init()
    {
        base.Init();

        SceneType = Define.Scene.Login;
        Screen.SetResolution(800, 600, false);

        StartCoroutine(_Init());
    }

    IEnumerator _Init()
    {
        NetworkManager networkManager = Managers.Network;
        yield return new WaitUntil(() => { return networkManager.IsConnected; });
        
        Managers.UI.ShowSceneUI<LoginPopup>();
    }

    public override void Clear()
    {
        Managers.UI.Clear();
    }
}
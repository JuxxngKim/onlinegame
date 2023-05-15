using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameScene : BaseScene
{
    protected override void Init()
    {
        base.Init();

        SceneType = Define.Scene.Game;
        Screen.SetResolution(640, 480, false);
        
        Managers.UI.Clear();
        Managers.Map.LoadMap(1);
    }

    public override void Clear()
    {
        
    }

    public void OnApplicationQuit()
    {
        Managers.Network.DisConnect();
    }
}

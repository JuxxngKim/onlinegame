using System.Collections;
using System.Collections.Generic;
using Protocol;
using UnityEngine;

public class GameScene : BaseScene
{
    protected override void Init()
    {
        base.Init();

        SceneType = Define.Scene.Game;
        Managers.Map.LoadMap(1);

        // C_EnterGame enterGame = new C_EnterGame();
        // Managers.Network.Send(enterGame);
    }

    public override void Clear()
    {
        
    }

    public void OnApplicationQuit()
    {
        Managers.Network.DisConnect();
    }
}

// This program is a part of NITAN MudLIB
// /adm/daemons/x_questd.c 宗師口訊任務守護進程
// from huaxia

#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

public int query_quest(object me, object ob)
{
    mapping temp, quest = ([]);
    string arg, msg, str, place, where, question, answer;
    object npc;
    object maze_target;
    object maze_object;

    temp = X_PointD->get_question();    //由守護程序產生點陣任務
    // temp =  ANTI_ROBOT->get_question();
    question = temp["question"];
    answer = temp["answer"];

    message("vision", sprintf("%s小聲的對%s吩咐着什麼，%s一邊聽，"
                              "一邊不住的點頭。\n",
                                ob->name(1), me->name(), me->name()),
                                environment(me), ({ me }));

    npc = new(CLASS_D("generate") + "/player_npc.c");   //生成收訊人
    FUBEN_D->clear_fuben("ultra",query("id", me));
    maze_object=get_object("/f/ultra/"+query("id", me)+"/maze");
    maze_object->set_maze_boss(npc);
    //maze_target = MAZE_D->create_maze(npc);
    maze_target=get_object("/f/ultra/"+query("id", me)+"/maze/exit");
    npc->move(maze_target);
    npc->set_from_me(ob, 1);
    set_temp("quester",query("id",  me), npc);
    set("ultra_whisper",query("id",  me), npc);

    msg = sprintf("\n%s對你説道：你趕緊走一趟，將這個口訊傳送"
                  "(whisper)給%s，據説他正在一個迷宮中，不得延誤：\n",
                    ob->name(1), npc->name(1));
    msg += question;

    //quest["maze"]=query("maze/mazename", maze_target);
    quest["maze"] = maze_object;
    quest["object"] = base_name(npc);
    quest["bonus"] = 200+random(51);
    quest["name"] = npc->name(1);
    quest["id"]=query("id", npc);
    quest["answer"] = answer;
    quest["type"] = "傳";
    switch(query("id", ob) )
    {
        case "dugu qiubai":
        quest["dgmsg"] = msg;
        str = "quest_dg";

        break;

        case "kuihua taijian":
        quest["khmsg"] = msg;
        arg = "player_npc";
        str = "quest_kh";
        break;

        case "huang shang":
        quest["msg"] = msg;
        str = "quest_hs";
        break;

        case "nanhai shenni":
        quest["msg"] = msg;
        str = "quest_sn";
        break;
    }

    set(str, quest, me);
    me->start_more(msg);

    return 1;
}
// 本文件被 all_room_info_hj.h
// 及 1_room_info_special.h 
// 在  void init() 內調用。

// naihe 0:29 03-10-21


// 函數名、前後 {} 符號在這裏都是不需要的，放在這裏擺個樣子，看着清晰些
//void init()
//{

    object me = this_player();

    if( query_temp("huanjing", me) != "start" && !query("hj_game/npc", me) )
    {
        remove_call_out("get_out_here");
        call_out("get_out_here",1, me);
    }
    // 玩家在遊戲時，將保持所有狀態飽滿。
    if( query_temp("huanjing", me) == "start" )
        full_all( me );

    if( query("room_mark") != 1 && query("hj_game/npc", me) )
        return;
// 如果不是 1 號房間，來的又是 NPC 的話，直接 return 得了，免得
// add_action() 很耗資源。
// 若是NPC，還要進行一些其他的動作，不可以在這裏 return 。

    // 禁止的指令
    add_action( "block_cmds", ({
        "exercise", "dazuo", "respirate",
        "tuna", "practice", "lian",  "exert",
        "study", "du", 
        "to", "scheme", "put",
        "paimai", "jiaoyi", "paimai*", "jiaoyi*",
        "kill", "yun", "pfm", "perform", "hit", "throw", "shoot", "steal", "fight",
        "score", "hp", "hp2", "score2", "score3", "scorenew", "jifa", "enable",
        "jiali", "jiajin", "enforce", "enpower", "prepare", "bei", "inventory",
        "xue", "learn", "skills", "cha", "quest", "questobj",
        "wield", "unwield", "wear", "remove", 
        "new", "new*", "menpai", "menpai*", "jiaoyi", "jiaoy*", "rumor", "rumor*",
        "bangpai", "bangpai*", 
        "bunch", "store", "take", "qu", "cun", 
        "bid", "auction",
    }) );
    add_action("do_look","look");
    add_action("do_get","get");
//}

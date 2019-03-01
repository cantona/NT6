inherit ROOM;

void create()
{
        set("short", "迷宮出口");
        set("long", @LONG
這是一間寬敞的石屋，四周巨石壘就的牆壁泛出幽幽的青色光芒，兩盞青銅
燈吐出一尺高的火燄，飄忽閃爍，偶然有燈花爆裂的輕響，更令人感到窒息般的
寂靜。地上是丈許見方的青石板舖就，房間中央一塊白色石板格外醒目，上面雕
刻著細密的圖紋，讓人不由自主的想上前查看（mazemap）一番。
LONG );
        set("no_clean_up", 1);
        set("no_drop", 1);
        set("no_sleep_room", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("exits", ([
                "east":__DIR__"maze/exit", 
                "out": "/d/city/wumiao", 
        ]));  
                    
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "out" && userp(me) && query("exits/out"))
        {
                FUBEN_D->clear_fuben("ultra", query("id", me));
        }
        
        return ::valid_leave(me, dir);
}


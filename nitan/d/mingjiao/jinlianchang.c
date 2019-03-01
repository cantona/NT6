// Code of JHSH
// Room: /d/mingjiao/jinlianchang.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "精練場");
        set("long", @LONG
地是青磚舖，壁為紅牆砌。東邊置有兵器架，十八般兵器，無一
不有。再朝西面看，左有梅花樁，右是鐵沙場，齊備非常。場子南邊
齊整地放著百來個大小不一的青石鎖，不時有幾個明教弟子過去提舉
兩下。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"rjqlwch",
]));
        set("objects",([
                __DIR__"obj/huolu" : 1,
]));

        set("no_fight", 1);
        set("no_sleep", 1);
        set("no_steal", 1);
        set("no_clean_up", 0);
        set("cost", 1);

        setup();

}

int valid_leave(object me, string dir)
{
        if( dir == "north" && query_temp("refining", this_player()) )
               return notify_fail("你正在打鐵，不能離開這裡！\n");
        return ::valid_leave(this_player(), dir);
}
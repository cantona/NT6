//Room: /d/dali/zhulou5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","祭祀屋");
        set("long",@LONG
此間乃竹樓頂層，是一間寬敞的大屋，正中一座祭台上十二白石
圍成一圈，當中立有一面竹牌，上繪本族的蛇神圖畫；圈內另有幾面
稍小的竹牌，上書族內祖先姓名尊號；祭台前香火貢品整齊放置，時
有族人前來頂禮膜拜。
LONG);
        set("objects", ([
           __DIR__"npc/jisi": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "down"  : __DIR__"zhulou4",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6950);
	set("coor/z", 20);
	setup();
}

void init()
{
        object me = this_player();
        if( query_temp("xuncheng", me) )
        {
                set_temp("dali_xc/zl5", 1, me);
        }
}
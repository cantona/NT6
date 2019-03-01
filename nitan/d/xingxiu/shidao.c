// Room: /d/xingxiu/shidao.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;

void create()
{
        set("short", "石道");
        set("long", @LONG
這是一條兩旁點綴花卉的小徑。花兒發出的香味多多少少沖淡了周
圍彌漫著沼澤的瘴氣。來來往往都是星宿弟子，而且都是男的，哼著小
曲。西邊有一山洞，洞裡不時傳來嬉笑聲，其中也夾雜了哭叫求饒聲。
LONG
        );
        set("outdoors","xingxiu");
        set("exits", ([ 
                "east"  : __DIR__"xiaojing",
                "enter" : __DIR__"xiaoyao",
        ]));
        set("objects", ([ 
                CLASS_D("xingxiu")+"/caihua" : 1,
        ]) );
        set("coor/x", -50200);
        set("coor/y", 20200);
        set("coor/z", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if (dir =="enter" )
        {
                if (present("caihua zi", environment(me)))
                {
                        if (!myfam || myfam["family_name"] != "星宿派") 
return notify_fail("採花子擋住了你：我的小妞可不是給你們邪派弟子準備的！\n");
                        if( query("gender", me) == "無性" )
return notify_fail("採花子擋住了你，一臉譏笑：您這小身板還想玩妞？別開玩笑了。\n");
                        if( !query_temp("marks/花", this_player()) )
return notify_fail("採花子擋住了你：喂，你總該意思意思吧？\n");
                }
                return 1;
        }
        return ::valid_leave(me, dir);
}

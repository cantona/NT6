// shaluo.c

inherit ROOM;

void create()
{
        set("short", "莎蘿坪");
        set("long", @LONG
沿着玉泉，踏過累累石澗，由山徑迤邐而上，就來到了莎蘿坪。
從這裏山路開始陡峭，南面一條迂迴盤旋的山道，稱作「十八盤」，
通往山上。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "northwest" : __DIR__"path1",
                "northeast" : __DIR__"shanhongpb",
                "southup"   : __DIR__"yunmen",
        ]));
        set("objects", ([
                __DIR__"npc/haoke": 2,
        ]));
        set("outdoors", "huashan" );
        setup();
        replace_program(ROOM);
}
 
void init()
{
        object me = this_player();
        
        if( query_temp("xunshan", me) )
                set_temp("xunshan/shaluo", 1, me);
                
        return;
}
// Room: /d/guiyun/shiqiao.c
// Last Modified by winder on Jul. 9 2001

inherit ROOM;

void create()
{
        set("short", "大石橋");
        set("long",@LONG
這是歸雲莊前的石橋，再向西就進莊了。向莊子裡望去，但見樓閣紆連，
竟是好大一座莊院。
LONG );
        set("exits",([
                "north" : __DIR__"damen",
                "east"  : __DIR__"road4",
        ]) );
        set("no_clean_up",0);
        set("outdoors", "guiyun");
        set("coor/x", 280);
        set("coor/y", -840);
        set("coor/z", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "east")
        {
                write("莊前有一個依據九宮算術布成的桃花陣。\n");
                if( (query("family/family_name", me) == "桃花島" && 
                        me->query_skill("qimen-wuxing", 1) > 14) ||
                        me->query_skill("qimen-wuxing", 1) > 39)
                        write( "由于你平常看慣了這些簡易的陣法，所以不用細想，信步就走出了陣！\n");
                else {
                        set_temp("jiugong_dir", "e", me);
                        me->move(__DIR__"jiugong" + (random(9) + 1));
                        return -1;
                }
        }
        return ::valid_leave(me, dir);
}

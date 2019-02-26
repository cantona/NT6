// yanfeng.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "巖縫");
        set("long", @LONG
忽然，你感覺到被什麼東西鈎了一下，原來是一棵橫着伸出懸崖的
古鬆止住了下墜之勢，細看山崖中裂開了一條大縫，似乎可以由那裏攀
緣而下。
LONG );
        set("exits", ([
                "down" : __DIR__"gudi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50010);
        set("coor/y", -21060);
        set("coor/z", -30);
        setup();
}

int valid_leave(object me,string dir)
{
        if(dir=="down") 
        tell_object(me,"你攀着巖縫，很艱難地向下爬。哎呀唷。，哎呀。。唷。。\n");
        return ::valid_leave(me,dir);
}
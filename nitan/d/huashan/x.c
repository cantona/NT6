#include <ansi.h>

inherit ROOM;

void create()
{
        object ob;
        set("short", "空室");
        set("exits", ([
                "out"   : __DIR__"s",
        ]));

        set("long", @LONG
這是一間空曠的石室，不遠處有個一石凳，你不禁想象這裏曾經
像是有人在上面來打坐或者參悟武學至高境界。你隱約發現前方石壁
（bi）上像是刻着什麼東西。
LONG );
        set("item_desc", ([
               "bi"  :   HIW "\n\t\t無\n\t\t招\n\t\t勝\n\t\t有\n\t\t招\n\n」" NOR,
        ]));                       
        
        set("no_clean_up", 0);
        ob = find_object("/clone/lonely/book/dugubook");
        if (! ob) ob = load_object("/clone/lonely/book/dugubook");
        setup();
        if (! environment(ob) /*&& random(10) < 5*/)
        {

                  ob->move(this_object());
        }
        else destruct(ob);

        replace_program(ROOM);
}
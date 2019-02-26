inherit ROOM;
void create()
{
        object item, con;

        set("short", "萬安寺四樓大廳");
        set("long", @LONG
這裏是萬安寺四樓的大廳，相當的寬敞。一個明豔少女正座中堂，少女前方
有一塊巨大的紅木製武器架，左右站滿了親兵，排場很是氣派。
LONG );
        set("exits", ([ 
                "down" : "/d/tulong/yitian/was_lou3",
        ]));
        set("objects", ([
                "/d/tulong/yitian/npc/ada" : 1,
                "/d/tulong/yitian/npc/aer" : 1,
                "/d/tulong/yitian/npc/asan" : 1,
                "/d/tulong/yitian/npc/he" : 1,
                "/d/tulong/yitian/npc/zhao" : 1,
                "/d/tulong/yitian/obj/shelf" : 1,
                "/clone/npc/walker" : 1,
        ]) );

        setup();

        con = present( "shelf", this_object());
        item = find_object("/d/tulong/obj/yitianjian");
        if( !objectp(item) || !environment(item) ) {
                item = get_object("/d/tulong/obj/yitianjian");
                item->move(con);
                item->start_borrowing();
        }
}

void reset()
{
        object item, con;
        ::reset();
        con = present( "shelf", this_object());
        item = find_object("/d/tulong/obj/yitianjian");
        if( !objectp(item) || !environment(item) ) {
                item = get_object("/d/tulong/obj/yitianjian");
                item->move(con);
                item->start_borrowing();
        }
}

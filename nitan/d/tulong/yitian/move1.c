inherit ROOM;

void create()
{
        set("short", "元大都城中心");
        set("long", @LONG
這裏是元大都城的中心，也就是後來北京城的前身。灰色的城牆給人以莊嚴
肅穆之感，遠遠望去，城樓的輪廓益發顯得雄偉高大，一條護城河繞城而過。
LONG );
        set("no_fight", 1);
        set("no_steal", 1);
        set("no_beg",1);

        set("objects", ([
                "/d/beijing/npc/maiyi1" : 1,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("outdoors", "beijing");
        setup();
        replace_program(ROOM);
}


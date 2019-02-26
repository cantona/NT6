inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @LONG
這裏是後院外了，四周都是菜地，往北是個小山坡，東西
面都是用籬笆圍起的菜地，種着各樣的菜，籬笆很破爛，搖搖
欲墜，看來這裏沒什麼人打理。
LONG);
        set("no_fight", 1);
        set("exits", ([
              "west" : __DIR__"guofu_caidi2",
              "east" : __DIR__"guofu_caidi1",
              "south" : __DIR__"guofu_houyuan2",
        ]));
        set("outdoors", "wuguan");
        setup();
        replace_program(ROOM);
}

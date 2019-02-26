inherit ROOM;

void create()
{
    set("short", "墓地");
        set("long", @LONG
這裏是黑木崖日月神教教眾的墓地。墓地周圍種了一些矮矮的花
樹。樹上的白花星星點點。白花中間是一高大的石碑(bei)，整個墓地
乾乾淨淨，顯然天天有人打掃。
LONG );
        set("exits", ([
            "west"      : __DIR__"grass1",
        ]));
        set("item_desc", ([
            "bei": "上面刻着：神教子民，永生不滅。\n"
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
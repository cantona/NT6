inherit ROOM;

void create()
{
        set("short", "畫廊");
        set("long", @LONG
這是一條非常精美的長廊，柱子和欄桿是用華貴的紫檀木制成，
上面雕飾著美麗的圖畫，畫工精巧，美不勝收。地板不知是用什麼材
料做的，走在上面毫無聲息，你只感到腳下軟軟的，非常舒服。走廊
東面是一間房間，裡面不時傳出幾聲女子的嬌叱。
LONG );
        set("exits",([
                "north" : __DIR__"changl3",
                "east" : __DIR__"liangong",
                "west" : __DIR__"changl8",
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
inherit ROOM;

void create()
{
      set("short", "西側殿");
        set("long", @LONG
這裏是金頂華藏庵西側殿，是接待香客及來賓的地方。殿內擺着
幾張桌子，桌旁圍放數把椅子。牆上懸着幾幅字畫，牆邊一排書架，
架上擺滿經書。幾位進香客正在品茶養神，欣賞牆上的字畫或翻閲架
上的經書。還有兩個二十來歲的姑娘在向一位師太打聽有關出家的事。
一個十來歲的小師太正在忙前忙後招待客人。南邊有扇窗子(chuang)。
LONG );
              set("objects", ([
                   CLASS_D("emei") + "/wenqing" : 1,
              ]));
              set("item_desc", ([
                  "chuang" : "窗外可以看到峨眉山的秀麗山景。\n",
            ]));

        set("exits",([
                "east"   : __DIR__"hcazhengdian", 
              ]));
              set("coor/x", -570);
        set("coor/y", -320);
        set("coor/z", 220);
        setup();
}

void init()
{
        add_action("do_jump", "jump");
}

int do_jump(string arg)
{
        object me = this_player();

        if (! arg || arg != "chuang")
                return 0;

        message_vision("$N趁人不注意，跳出窗外。\n", me);
        me->move(__DIR__"xiaoshulin1");
        message_vision("$N從華藏庵裏跳窗出來。\n", me);
        return 1;
}
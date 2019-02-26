inherit ROOM;

void create()
{
          set("short", "畫廊");
        set("long", @LONG
這是一條非常精美的長廊，柱子和欄杆是用華貴的紫檀木製成，
上面雕飾着一些美麗的圖畫，畫工精巧，美不勝收。地板不知是用什
麼材料做的，走在上面毫無聲息，你只感到腳下軟軟的，非常舒服。
走廊西面通往本派的練功寶地玄冰室。
LONG );
          set("exits",([
                      "east" : __DIR__"changl10",
                      "west" : __DIR__"xuanbing",
          ]));
        set("objects",([
                CLASS_D("lingjiu") + "/cheng" : 1,
        ]));
          set("no_clean_up", 0);
          setup();
          replace_program(ROOM);
}
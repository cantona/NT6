inherit ROOM;

string* names = ({
        __DIR__"obj/mala-doufu",
        __DIR__"obj/bocai-fentiao",
        __DIR__"obj/shanhu-baicai",
        __DIR__"obj/liuli-qiezi",
});

void create()
{
      set("short", "齋堂");
        set("long", @LONG
這裡便是峨嵋華藏庵的齋堂。齋堂裡擺滿了長長的餐桌和長凳，
幾位小師太正來回忙碌著布置素齋。桌上擺了幾盆豆腐，花生，青菜
以及素鴨等美味素食。齋堂後面有一道門通往華藏庵儲物間，北邊的
走廊通向廣場。
LONG );
      set("exits", ([
          "south" : __DIR__"chuwujian", 
          "north" : __DIR__"hcaeast2", 
      ]));

      set("objects",([
           __DIR__"obj/qingshui-hulu" : 1,
           names[random(sizeof(names))]: 1,
           names[random(sizeof(names))]: 1,
           names[random(sizeof(names))]: 1,
      ]));
      setup();
      replace_program(ROOM);
}
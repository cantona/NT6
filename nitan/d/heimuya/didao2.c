//room: didao2.c
inherit ROOM;

void create()
{
  set("short","秘道");
        set("long", @LONG
你來到了一條秘道，看樣子它不太平常，若隱若顯的幾盞油燈，
昏暗如豆但是看上去前方似有光亮，你要是覺得害怕，現在回頭還是
可以的，不過這異常的幽靜卻也極大激發了你的好奇心，大丈夫死又
何足道載，真是勇氣可佳。
LONG );

  set("exits",([
      "west" : __DIR__"didao1", 
      "south" : __DIR__"didao5",
  ]));
  set("no_clean_up", 0);
  setup();
  replace_program(ROOM);
}
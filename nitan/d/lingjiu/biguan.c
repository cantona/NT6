inherit ROOM;
void create()
{
          set("short", "閉關室");
        set("long", @LONG
這裏當年本是天山童姥閉關修練的地方，至天山童姥仙去之後，
虛竹子便將此處挪出，讓梅蘭竹菊四姐妹居住。
LONG );
          set("sleep_room", 1);
          set("exits",([
                      "south" : __DIR__"men3",
          ]));
        set("objects",([
                CLASS_D("lingjiu") + "/jujian" : 1,
                "/kungfu/class/lingjiu/tonglao" : 1,
        ]));

          setup();
          replace_program(ROOM);
}
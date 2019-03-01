inherit ROOM;

void create()
{
      set("short", "九十九道拐");
        set("long", @LONG
這是著名的「九十九道拐」，道路紆曲陡豎千折百回。據說過去
曾有個百余歲的瘋僧至此，見一巨蟒擋路，便念咒驅蟒。但人們得知
此處有巨蟒出沒後，便再也無人敢碰這裡的草木並以「龍居」名之。
由此東可至千佛庵，西達九老洞。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "southwest" : __DIR__"jsjdg3",
          "eastdown"  : __DIR__"jsjdg1",
      ]));
      set("coor/x", -490);
        set("coor/y", -240);
        set("coor/z", 120);
        set("coor/x", -490);
        set("coor/y", -240);
        set("coor/z", 120);
        setup();
      replace_program(ROOM);
}
//room: /d/mingjiao/qiandian.c
inherit ROOM;

void init();

void create()
{
        set("short","明教前殿");
        set("long", @LONG
你來到這裏，放眼窗外望去，漫漫崑崙雪山，晶瑩剔透，蒼天浩
浩，白雲悠悠。東方沃野千里，楚天遼闊；西面高山巍巍，迤邐萬里。
這裏就是叱吒武林八百年的明教總舵的前殿。
LONG );
       set("exits",([
           "east"      : __DIR__"eastdian",
           "west"      : __DIR__"westdian",
           "north"     : __DIR__"dadian",
           "southdown" : __DIR__"square",
       ]));
       setup();
       replace_program(ROOM);
}

//  instrument: dongbula.c
// Jay 3/18/96

inherit ITEM;
int do_play(string arg);

//void setup()
//{}

void init()
{
        add_action("do_play", "play");
}

void create()
{
        set_name("冬不拉", ({"dongbula"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把維吾爾族的絃樂器冬不拉。你可以演奏(play)它。\n");
                set("value", 100);
        }
//        setup();
}

int do_play(string arg)
{
        if (!id(arg))
                return notify_fail("你要演奏什麼？\n");
        switch( random(3) ) {
                case 0:
                        say(this_player()->name() + "彈起冬不拉，深情地唱道：\n"
"在那遙遠的地方，有位好姑娘。每當人們走過她的氈房，總要把她\n"
"深情地凝望。\n");
                        write(this_player()->name() + "彈起冬不拉，深情地唱道：\n"
"在那遙遠的地方，有位好姑娘。每當人們走過她的氈房，總要把她\n"
"深情地凝望。\n");

                        break;
                case 1:
                        say(this_player()->name() + "彈起冬不拉，快樂地唱道：\n"
"大阪城的石頭圓又硬嘍西瓜大又甜嘍，大阪城的姑娘辮子長嘍兩隻眼睛真漂亮。\n");
                        write(this_player()->name() + "彈起冬不拉，快樂地唱道：\n"
"大阪城的石頭圓又硬嘍西瓜大又甜嘍，大阪城的姑娘辮子長嘍兩隻眼睛真漂亮。\n");

                        break;
                case 2:
                        say(this_player()->name() + "彈起冬不拉，哀傷地唱道：\n"
"戈壁灘上的一朵清泉，冰山上的一朵雪蓮，風暴不會永遠不停，啊啊啊，什麼時候啊，"
"才能見到你的笑臉。\n");
                        write(this_player()->name() + "彈起冬不拉，哀傷地唱道：\n"
"戈壁灘上的一朵清泉，冰山上的一朵雪蓮，風暴不會永遠不停，啊啊啊，什麼時候啊，"
"才能見到你的笑臉。\n");

                        break;
        }
        return 1;
}
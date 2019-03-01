// temp-room.c
// This object mustn't be any error, beacuse any character
// move from an room to another room, this object will be
// used.

#pragma optimize
#pragma save_binary

inherit ROOM;

void create()
{
        seteuid(getuid());
        set("short", "無邊落木");
        set("long", "這是一處渺無人跡的地方。\n");
        set("no_fight", 1);
        set_heart_beat(1);
}

void heart_beat()
{
        object *ob;

        // Clear the room's link
        SIMUL_EFUN_OB->clear_link_temp();

        ob = all_inventory(this_object());
        if (pointerp(ob) && sizeof(ob) > 0)
        {
                // Moved all the item to VOID_OB
                ob->apply_moved_function(0);
                ob->move(VOID_OB);
        }
}

int clean_up()
{
        heart_beat();
        destruct(this_object());
        return 0;
}
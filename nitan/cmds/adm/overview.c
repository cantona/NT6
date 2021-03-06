// overview.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *ob;
        int i, m;

        if (! me->is_admin())
                return 0;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
                
        switch(arg) {
                case "user":
                        ob = users();
                        printf("共有 %d 個使用者物件　\n", sizeof(ob));
                        break;
                case "living":
                        ob = livings();
                        printf("共有 %d 個生物(含使用者)物件　\n", sizeof(ob));
                        break;
                case "char":
                        ob = objects( (: $1->is_character() && !clonep($1) :) );
                        printf("共有 %d 種人物物件 master copy 被載入　\n", sizeof(ob));
                        break;
                case "npc":
                        ob = filter_array( livings(),
                                (: $1->is_character() && !userp($1) && clonep($1) :) );
                        printf("共有 %d 個 NPC 物件　\n", sizeof(ob));
                        break;
                case "combat":
                        ob = objects( (: $1->is_fighting() :) );
                        printf("共有 %d 個人物正在戰鬥狀態　\n", sizeof(ob));
                        break;
                case "kill":
                        ob = objects( (: $1->is_killing() && $1->is_fighting() :) );
                        printf("共有 %d 個人物正在性命相搏的戰鬥狀態　\n", sizeof(ob));
                        break;
                case "hunt":
                        ob = objects( (: $1->is_killing() :) );
                        printf("共有 %d 個人物正和其他人物互相仇恨　\n", sizeof(ob));
                        break;
                case "heart beat":
                        ob = objects( (: query_heart_beat :) );
                        printf("共有 %d 個物件的 heart beat 為有效狀態　\n", sizeof(ob));
                        break;
                case "virtual":
                        ob = objects( (: virtualp :) );
                        printf("共有 %d 個虛擬物件　\n", sizeof(ob));
                        break;
                case "room":
                        ob = objects( (: function_exists("create_door", $1) :) );
                        printf("共有 %d 個房間　\n", sizeof(ob));
                        break;
                case "special room":
                        // inherits won't work if master copy got cleaned up.
                        if( !find_object(ROOM) ) ROOM->foo();
                        ob = objects( (: inherits(ROOM, $1) :) );
                        printf("共有 %d 個物件繼承標準房間　\n", sizeof(ob));
                        break;
                case "equip":
                        // inherits won't work if master copy got cleaned up.
                        if( !find_object(F_EQUIP) ) F_EQUIP->foo();
                        ob = objects( (: inherits(F_EQUIP, $1) :) );
                        printf("共有 %d 個物件繼承標準裝備　\n", sizeof(ob));
                        break;
                case "object":
                        ob = objects();
                        printf("共有 %d 個物件被載入　\n", sizeof(ob));
                        break;
                default:
                        return notify_fail("指令格式：overview <topic>\n");
        }
        m = 0;
        i = sizeof(ob);
        while(i--)
                m += memory_info(ob[i]);
        printf("總共使用 %d bytes 記憶體　\n", m);
        if( sizeof(ob) )
                printf("平均每個物件使用 %d bytes 記憶體　\n", m / sizeof(ob));
        return 1;
}

int help()
{
        write(@TEXT
指令格式：overview <主題>

主題:

user
living
room
char
npc
combat
hunt
object
equip
special room
kill
heart beat
virtual
TEXT
        );
        return 1;
}



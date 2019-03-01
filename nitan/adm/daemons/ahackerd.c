// ahackerd.c
// by Find.
// 防止猜密碼. 封賬號功能也在此實現.
// 此功能也有弊病，建議只對巫師賬號採取防猜保護。

#include <origin.h>

#define TIME_SEC        300
#define MAX_MISTAKE     3
#define LIST_FILE       "/adm/etc/blocklist"

#define DATA            DATA_DIR + "ahackerd.o"

mapping being_hacking = ([]);
nosave string *blocked_account = ({});

int block_account(string id);
int unblock_account(string id);

protected void check_same_ip_number(string ip);

void init_blocklist()
{
        if (previous_object() && (geteuid(previous_object()) != ROOT_UID))
                return;

        if (file_size(LIST_FILE) < 0)
                return;

        blocked_account =  filter_array(explode(read_file(LIST_FILE), "\n") - ({ "" }), (: $1[0] != '#' :));
}

private void write_list()
{
        write_file(LIST_FILE,implode(blocked_account,"\n"),1);
}

int save()
{
        save_object(DATA);
}

void create()
{
        seteuid(getuid());
        if( !restore_object(DATA) )
        {
                being_hacking = allocate_mapping(0);

                save_object(DATA);
        }
        init_blocklist();
}

void passwd_mistake(string id,string ip)
{
        string *hacking;

        if(previous_object() && (geteuid(previous_object()) != ROOT_UID))
                return;
        if(!id || !stringp(id))
                return;

        hacking = keys(being_hacking);
        if(!sizeof(hacking) || member_array(id,hacking) == -1)
        {
                being_hacking += ([ id : 1 ]);
                log_file("hacking",sprintf("賬號:%s 密碼輸入不正確.時間:%s 來自:%s\n",
                        id,ctime(time()),ip));
                save();
                check_same_ip_number(ip);
                return;
        }

        else if( (being_hacking[id] + 1) >= MAX_MISTAKE )
        {
                block_account(id);
                map_delete(being_hacking,id);
                save();
                CHANNEL_D->do_channel(this_object(),"sys",sprintf("賬號 %s：連續5次密碼輸入錯誤，此賬號被封鎖予以保護。\n",
                        capitalize(id)));
                log_file("hacking",sprintf("***賬號:%s 連續"+MAX_MISTAKE+"次密碼輸入不正確被懷疑受到攻擊.\n"
                        +"   于 %s 被暫時封鎖予以保護.最後一次攻擊來自%s.\n",id,ctime(time()),ip));
                check_same_ip_number(ip);
                return;
        }

        else
        {
                being_hacking[id] += 1;
                save();
                log_file("hacking",sprintf("賬號:%s 密碼輸入不正確.時間:%s 來自:%s\n",
                        id,ctime(time()),ip));
                save();
                check_same_ip_number(ip);
        }
}

void success_login(string id)
{
        string *hacking;

        if(previous_object() && (geteuid(previous_object()) != ROOT_UID))
                return;
        if(!id || !stringp(id))
                return;

        if(!mapp(being_hacking) || being_hacking == ([]))
                return;

        hacking = keys(being_hacking);
        if(!sizeof(hacking))
                return;
        if(member_array(id,hacking) != -1)
        {
                map_delete(being_hacking,id);
                save();
        }
        return;
}

// return 0:已經被封鎖 1:成功封鎖.
int block_account(string id)
{
        string file;
        if(!id || !stringp(id))
                return 0;

        if(!previous_object())
                return 0;
        file = file_name(previous_object());
        if( (origin() == ORIGIN_CALL_OTHER) &&(file != "/cmds/arch/block") )
                return 0;

        if(member_array(id,blocked_account) != -1)
                return 0;
        else
        {
                blocked_account += ({ id });
                write_list();
                return 1;
        }
}

// return 0:本身未被封鎖 1: 成功解除封鎖.
int unblock_account(string id)
{
        string file;

        if(!id || !stringp(id))
                return 0;

        if(!previous_object())
                return 0;
        file = file_name(previous_object());
        if( (origin() == ORIGIN_CALL_OTHER) && (file != "/cmds/arch/block") )
                return 0;

        if(member_array(id,blocked_account) == -1)
                return 0;
        else
        {
                blocked_account -= ({ id });
                write_list();
                return 1;
        }
}

int query_block(string id)
{
        if(!pointerp(blocked_account) || blocked_account == ({}))
                return 0;
        else
                return member_array(id,blocked_account) !=-1;
}

string blocked_list()
{
        int i;
        string list = "";

        if(geteuid(previous_object()) != ROOT_UID)
                return "";

        if(!sizeof(blocked_account))
                return "目前"+MUD_NAME+"沒有任何賬號被封鎖。\n";
        else
        {
                for(i=0; i<sizeof(blocked_account); i++)
                {
                        list += sprintf("%-15s%c",
                        blocked_account[i],((i%5==4) ? '\n' : ' '));
                }
                list += "\n";
                return list;
        }
}

protected void check_same_ip_number(string ip)
{
        object *objs;
        string *ids = ({});

        objs = filter_array(children(USER_OB),(: clonep :));

        for(int i=0;i<sizeof(objs);i++)
        {
                if(query_ip_number(objs[i]) == ip)
                        ids += ({ geteuid(objs[i]) });
        }

        if(!sizeof(ids))
                return;
        else
                log_file("hacking",sprintf("\t攻擊來自IP與在線人物 %s 的IP地址相同\n",
                        implode(ids,"、")));
}

string query_name()
{
        return "駐守精靈(AHACKER_D)";
}
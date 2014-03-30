package jp.tcc.ipmsg4a.messenger;

import java.util.Set;

import jp.tcc.ipmsg4a.model.Message;
import jp.tcc.ipmsg4a.model.User;

public interface Messenger {
	public Set<User> getUsers();
	public void sendMessage(Message message);
	public void setMessengerListener(MessengerListener listener);
}

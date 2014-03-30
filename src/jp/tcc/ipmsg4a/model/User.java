package jp.tcc.ipmsg4a.model;

public class User implements Comparable<User>{
	private String name;
	private String ipAddress;
	private Group group;
	
	public User(String name, String ipAddress, Group group){
		this.name = name;
		this.ipAddress = ipAddress;
		this.group = group;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setIpAddress(String ipAddress) {
		this.ipAddress = ipAddress;
	}

	public void setGroup(Group group) {
		this.group = group;
	}

	public String getName() {
		return name;
	}

	public String getIpAddress() {
		return ipAddress;
	}

	public Group getGroup() {
		return group;
	}

	@Override
	public int compareTo(User other) {
		return this.name.compareTo(other.name);
	}

}

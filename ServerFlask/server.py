from flask import Flask,redirect,url_for,request,render_template
import serial,time

ser = serial.Serial('COM6',9600)
ser.close()

app = Flask(__name__)
heatingStatus = "Stopping"


@app.route('/login',methods=['POST'])
def login():
	ser.open()
	if(ser.isOpen()):
		global heatingStatus
		ss = str(request.form['fname'])
		print ss[0]
		if(ss[0] == "1"):
			heatingStatus = "Heating"
		if(ss[0] == "0"):
			heatingStatus = "Stopping"
		time.sleep(2)
		ser.write(ss[0])
		ser.close()
	print request.form['fname']
	return redirect(url_for('test'))

@app.route('/')
def index(name=None):
	return render_template('index.html',name=name)

@app.route('/ab18b3e58a3b1bb5106ced208a8bd460')
def test():
	time.sleep(2)
	ser.open()
	if(ser.isOpen()):
		time.sleep(2)
		ser.write('2')
		t = ser.readline()
		ser.close()
	return render_template('test.html',name=heatingStatus,temp = t)

if __name__ == '__main__':
	#app.debug = True
	app.run(host='0.0.0.0')

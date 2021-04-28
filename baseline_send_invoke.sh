# Now send invoke to driver only 
curl -H "Content-Type:application/json" -X POST -d '{"message": "DD"}' http://127.0.0.1:5000/invoke

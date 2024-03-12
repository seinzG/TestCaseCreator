import os.path

from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ["https://www.googleapis.com/auth/spreadsheets.readonly"]

def main():
  try:
    creds = None
    if os.path.exists("token.json"):
        creds = Credentials.from_authorized_user_file("token.json", SCOPES)

    service = build("sheets", "v4", credentials=creds)

    # Call the Sheets API
    sheet = service.spreadsheets()
    # result = (
    #     sheet.values()
    #     .get(spreadsheetId=SAMPLE_SPREADSHEET_ID, range=SAMPLE_RANGE_NAME)
    #     .execute()
    # )

    sheet_metadata = service.spreadsheets().get(spreadsheetId=SAMPLE_SPREADSHEET_ID).execute()
    properties = sheet_metadata.get('sheets')
    result = []
    for  item in properties:
      # if item.get("properties").get('title') == 'SHEET_TITILE':
      #     sheet_id = (item.get("properties").get('sheetId'))
      print(item.get("properties").get('title'))


    return item.get("properties").get('title');


    # if not sheet_id:
    #   print("No data found.")
    #   return

    # print("Name, Major:")
    # for row in sheet_id:
    #   # Print columns A and E, which correspond to indices 0 and 4.
    #   print(f"sheet_id")
  except HttpError as err:
    print(err)


if __name__ == "__main__":
  SAMPLE_SPREADSHEET_ID = open('spreadsheet_id', 'r').readline().strip()
  main()

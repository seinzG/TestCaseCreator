
import sys
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.errors import HttpError

# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/spreadsheets']
SHEET_NAME = sys.argv[1][1:]

def get_row(spreadsheet_id, range_name):
  # print(range_name)
  """
  Creates the batch_update the user has access to.
  Load pre-authorized user credentials from the environment.
  TODO(developer) - See https://developers.google.com/identity
  for guides on implementing OAuth2 for the application.
  """
  #creds, _ = google.auth.default()
  creds = Credentials.from_authorized_user_file("token.json", SCOPES)
  # pylint: disable=maybe-no-member
  try:
    service = build("sheets", "v4", credentials=creds)

    result = (
        service.spreadsheets()
        .values()
        .get(spreadsheetId=spreadsheet_id, range=range_name)
        .execute()
    )
    rows = result.get("values", [])
    #print(f"{rows}")

    res_list = []

    for item in rows: 
        if item not in res_list: 
            res_list.append(item[0])
            # print(type(item))
            # print (item, end=" ")
    return res_list
  
  except HttpError as error:
    print(f"An error occurred: {error}")
    return error
    # return None
  
def update_values(spreadsheet_id, range_name, value_input_option, values):
  """
  Creates the batch_update the user has access to.
  Load pre-authorized user credentials from the environment.
  TODO(developer) - See https://developers.google.com/identity
  for guides on implementing OAuth2 for the application.
  """
  # print(range_name)
  creds = Credentials.from_authorized_user_file("token.json", SCOPES)
  # pylint: disable=maybe-no-member
  try:
    service = build("sheets", "v4", credentials=creds)
    values = [
        args
    ]
    body = {"values": values}
    result = (
        service.spreadsheets()
        .values()
        .update(
            spreadsheetId=spreadsheet_id,
            range=range_name,
            valueInputOption=value_input_option,
            body=body,
        )
        .execute()
    )

    sp = service.spreadsheets().get(
      spreadsheetId=spreadsheet_id
    ).execute()

    sheets = sp['sheets']
    for sheet in sheets:
        if sheet['properties']['title'] == SHEET_NAME:
            sheet_id = sheet['properties']['sheetId']
            break
    # print(sys.argv[1][1:])
    # print(index)
    service = build("sheets", "v4", credentials=creds)
    update_request = {
      #   "deleteDimension": {
      #       "range": {
      #           "sheetId": sheet_id,
      #           "dimension": "ROWS",
      #           "startIndex": index+1,
      #           "endIndex": index+2
      #       }
      # }
          'repeatCell': {
            'range': {
                'sheetId': sheet_id,
                'startColumnIndex': 0,              
                'endColumnIndex': 9,
                'startRowIndex': index+1,
                'endRowIndex': index+2
            },
            'cell':
                {
                    'userEnteredFormat': {
                        'backgroundColor': {
                            'red': 255 / 255,  # Normalize RGB values
                            'green': 255 / 255,
                            'blue': 255 / 255
                        }
                    }
                },
        "fields": "userEnteredFormat(backgroundColor)"  # Specify the fields to update
        }
    }
    update_requests = []
    update_requests.append(update_request)
    body = {"requests": update_requests}
    result = (
        service.spreadsheets().batchUpdate(
            spreadsheetId=spreadsheet_id,
            body=body
        )
        .execute()
    )
    # print(f"{result}")
    # print(f"{result.get('updatedCells')} cells updated.")
    print('Success')
    return result
  except HttpError as error:
    print(f"An error occurred: {error}")
    return error


if __name__ == "__main__":
  # Pass: spreadsheet_id,  range_name, value_input_option and  _values
  args = [string[1:] for string in sys.argv[2:11]]
  SAMPLE_SPREADSHEET_ID = open('spreadsheet_id', 'r').readline().strip()

  testCaseID = get_row(SAMPLE_SPREADSHEET_ID, sys.argv[1][1:]+"!A2:A")

  index = testCaseID.index(sys.argv[2][1:])

  update_values(
      SAMPLE_SPREADSHEET_ID,
      sys.argv[1][1:]+"!A"+str(index+2)+":I"+str(index+2),
      "USER_ENTERED",
      args,
  )